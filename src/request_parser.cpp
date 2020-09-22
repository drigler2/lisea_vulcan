/***************************************************************************
 Copyright (C) 2020 Damir Rigler

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; version 2 of the License.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 ***************************************************************************/

#include <request_parser.hpp>

namespace lisea {
namespace http {

const std::regex RequestParser::INIT_LINE_REGEX(
        "^([a-zA-Z]+)\\s([\\S]+)\\sHTTP\\/(\\d)\\.(\\d+)$");

const std::regex RequestParser::CRLF("(\r\n)+$");

/**
 *
 * TODO extern buffer config
 * TODO find buffer end
 *
 * **/
RequestParser::ResultResult RequestParser::parse(Request &r,
        std::array<char, 8192> &in_buffer) {
    const int INX_BFR_SIZE = 50;

    std::array<int, INX_BFR_SIZE> i_cart = { };
    int c_cart = 0;
    std::array<int, INX_BFR_SIZE> i_lnfd = { };
    int c_lifd = 0;

    // mark all CRLF
    for (int i = 0; i < in_buffer.size(); i++) {

        if (in_buffer[i] == '\r') {
            i_cart[c_cart++] = i;
        }
        else if (in_buffer[i] == '\n') {
            i_lnfd[c_lifd++] = i;
        }

        // not parsing the body
        // TODO drigler handle body
        if (i > 3 && in_buffer[i - 3] == '\r' && in_buffer[i - 2] == '\n'
                && in_buffer[i - 1] == '\r' && in_buffer[i] == '\n') {
            break;
        }

    }

    /**
     * go trough marked CRLF, copy text from buffer to Request.
     * discard CRLF
     *
     * Parsing is done in accordance with standard. ish.
     *
     * note that indices are compared for \r and \n,  not actual values.
     *
     * TODO parse headers
     * **/
    int ig = 0;
    while (i_cart[ig] != 0 && i_lnfd[ig] != 0) {

        if (i_cart[ig] == (i_lnfd[ig] - 1) && ig == 0) {

            r.method = std::string(&in_buffer[0], &in_buffer[i_cart[ig]]);
            if (!is_req_first_line_valid(r.method)) {
                return ResultResult::BAD;
            }

            LOG->debug("r.method: {}; isValid: {}", r.method,
                    is_req_first_line_valid(r.method));
        }
        else if (i_cart[ig] == (i_cart[ig - 1] + 2)
                && ((i_lnfd[ig]) == (i_lnfd[ig - 1] + 2))) {

            LOG->debug("Found request end, exiting.....");

            return ResultResult::GOOD;
        }
        else if (i_cart[ig] != 0 && i_lnfd[ig] != 0) {

            if (!check_parse_header_line(r, in_buffer, i_lnfd[ig - 1] + 1, i_cart[ig])) {
                return ResultResult::BAD;
            }

            LOG->debug("r.header: {}",
                    std::string(&in_buffer[i_lnfd[ig - 1] + 1], &in_buffer[i_cart[ig]]));
        }

        ig++;
    }
    return ResultResult::INDETERMINATE;
}

bool RequestParser::check_parse_header_line(Request &r, std::array<char, 8192> &in_buffer,
        int start, int end) {

    int index = start;
    while (index != end) {
        if (in_buffer[index] == ' ' && in_buffer[index - 1] == ':') {
            r.headers.push_back(Header { //
                    std::string(&in_buffer[start], &in_buffer[index - 1]), //
                    std::string(&in_buffer[index + 1], &in_buffer[end]) });

            LOG->debug("r.header: {}; value: {}",
                    std::string(&in_buffer[start], &in_buffer[index - 1]),
                    std::string(&in_buffer[index + 1], &in_buffer[end]));

            return true;
        }

        index++;
    }

    return false;
}

bool RequestParser::is_req_first_line_valid(std::string &input) {
    std::match_results<std::string::const_iterator> what;

    if (std::regex_search(input, what, INIT_LINE_REGEX)) {

        LOG->debug("RequestParser::is_req_first_line_valid::Matched: {}", input);
        return true;
    }

    LOG->debug("RequestParser::is_req_first_line_valid::Failed: {}", input);
    return false;
}

}
} //NS
