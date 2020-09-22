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
#ifndef INCLUDE_REPLY_H
#define INCLUDE_REPLY_H

#include <vector>
#include <string>
#include <boost/asio.hpp>

#include "header.hpp"

namespace lisea {
namespace http {

struct Reply {
public:
    enum StatusType {
        OK = 200, BAD_REQUEST = 400, INTERNAL_SERVER_ERROR = 500
    } status;

    enum ContentType {
        TEXT, JSON
    };

    std::vector<boost::asio::const_buffer> to_buffers();
    static Reply stock_reply(StatusType status);
    static Reply business_reply(StatusType status, const std::string &ocontent);
    static Reply business_reply(StatusType status, const std::string &ocontent,
            ContentType contentType);

    std::vector<Header> headers;
    std::string content;
};

}
} //NS

#endif /* INCLUDE_REPLY_H */
