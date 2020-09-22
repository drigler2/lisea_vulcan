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
#ifndef INCLUDE_REQUEST_PARSER_H
#define INCLUDE_REQUEST_PARSER_H

#include <regex>
#include <string>
#include <spdlog/spdlog.h>
#include <regex.h>

#include "request.hpp"
#include "header.hpp"
#include "lisea_config.hpp"

namespace lisea {
namespace http {

class RequestParser {
public:

    RequestParser() :
            LOG(spdlog::get(lisea::http::LOGGER_NAME)) {
    }

    enum ResultResult {
        GOOD, BAD, INDETERMINATE
    };

    void reset();
    ResultResult parse(Request &r, std::array<char, 8192> &in_buffer);

private:
    std::shared_ptr<spdlog::logger> LOG;

    bool check_parse_header_line(Request &r, std::array<char, 8192> &in_buffer, int start,
            int end);

    static const std::regex INIT_LINE_REGEX;
    static const std::regex CRLF;

    ResultResult consume(Request &r, char input);
    bool is_req_first_line_valid(std::string &input);

};

}
} //NS

#endif /* INCLUDE_REQUEST_PARSER_H */
