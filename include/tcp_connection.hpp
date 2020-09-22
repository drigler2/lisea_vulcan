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
#ifndef INCLUDE_TCPCONNECTION_H
#define INCLUDE_TCPCONNECTION_H

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>

#include "header.hpp"
#include "reply.hpp"
#include "request_parser.hpp"
#include "request.hpp"
#include "snowflaked_service.hpp"

namespace lisea {
namespace http {

class ConnectionManager;

using boost::asio::ip::tcp;

class TcpConnection: public std::enable_shared_from_this<TcpConnection> {

public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

    TcpConnection(const TcpConnection&) = delete;
    TcpConnection& operator=(const TcpConnection&) = delete;

    TcpConnection(boost::asio::ip::tcp::socket soket1, ConnectionManager &manager) :
            //TODO clarify move
            soket(std::move(soket1)), //
            manager(manager), //
            LOG(spdlog::get(lisea::http::LOGGER_NAME)) {
    }

    tcp::socket& get_socket();

    void start(SnowflakedService &snowService);
    void stop();

private:
    std::shared_ptr<spdlog::logger> LOG;

    void do_read(SnowflakedService &snowService);
    void do_write();

    ConnectionManager &manager;
    tcp::socket soket; // spelling ok

    std::array<char, lisea::http::IN_BUFFER_LENGTH> in_buffer;
    std::vector<boost::asio::const_buffer> buffers;

    Request request;
    RequestParser parser;
    Reply reply;
};

} // namespace http
} // namespace server

#endif /* INCLUDE_TCPCONNECTION_H */
