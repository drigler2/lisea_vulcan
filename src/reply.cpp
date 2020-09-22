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

#include <reply.hpp>
#include <string>

namespace lisea {
namespace http {

using std::string;

namespace status_string {

const string ok = "HTTP/1.0 200 OK\r\n";
const string bad_request = "HTTP/1.0 400 Bad Request\r\n";
const string internal_server_error = "HTTP/1.0 500 Internal Server Error\r\n";

boost::asio::const_buffer to_buffer(Reply::StatusType status) {

    switch (status) {
    case Reply::OK:
        return boost::asio::buffer(ok);
    case Reply::BAD_REQUEST:
        return boost::asio::buffer(bad_request);
    case Reply::INTERNAL_SERVER_ERROR:
        return boost::asio::buffer(internal_server_error);
    }

    return boost::asio::buffer(internal_server_error);
}
}

namespace misc_strings {
const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

}

namespace stock_replies {
const char ok[] = "";
const char bad_request[] = "<html>"
        "<head><title>Bad Request</title></head>"
        "<body><h1>400 Bad Request</h1></body>"
        "</html>";
const char internal_server_error[] = "<html>"
        "<head><title>Internal Server Error</title></head>"
        "<body><h1>500 Internal Server Error</h1></body>"
        "</html>";

std::string to_string(Reply::StatusType status) {
    switch (status) {
    case Reply::OK:
        return ok;
    case Reply::BAD_REQUEST:
        return bad_request;
    case Reply::INTERNAL_SERVER_ERROR:
        return internal_server_error;
    }

    return internal_server_error;
}
}

std::vector<boost::asio::const_buffer> Reply::to_buffers() {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(status_string::to_buffer(this->status));

    for (std::size_t i = 0; i < this->headers.size(); i++) {
        Header &h = this->headers[i];
        buffers.push_back(boost::asio::buffer(h.name));
        buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
        buffers.push_back(boost::asio::buffer(h.value));
        buffers.push_back(boost::asio::buffer(misc_strings::crlf));
    }

    buffers.push_back(boost::asio::buffer(misc_strings::crlf));
    buffers.push_back(boost::asio::buffer(content));

    return buffers;
}

Reply Reply::stock_reply(StatusType status) {
    Reply r;
    r.status = status;
    r.headers.resize(2);
    r.headers[0].name = "Content-Length";
    // TODO check: number of bytes
    r.headers[0].value = std::to_string(r.content.size());
    r.headers[1].name = "Content-Type";
    r.headers[1].value = "text/html";

    return r;
}

Reply Reply::business_reply(StatusType status, const std::string &content) {
    Reply r;
    r.status = status;

    r.content = content;

    r.headers.resize(2);
    r.headers[0].name = "Content-Length";
    // TODO check: number of bytes
    r.headers[0].value = std::to_string(r.content.size());
    r.headers[1].name = "Content-Type";
    r.headers[1].value = "text/html";

    return r;
}

Reply Reply::business_reply(StatusType status, const std::string &content,
        ContentType content_type) {
    Reply r;
    r.status = status;

    r.content = content;

    r.headers.resize(2);
    r.headers[0].name = "Content-Length";
    // TODO
    r.headers[0].value = std::to_string(r.content.size());
    r.headers[1].name = "Content-Type";

    switch (content_type) {
    case TEXT:
        r.headers[1].value = "text/plain";
        break;
    case JSON:
        r.headers[1].value = "application/json";
        break;
    }

    return r;
}

}
} //NS
