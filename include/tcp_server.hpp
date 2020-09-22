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
#ifndef INCLUDE_TCPSERVER_H
#define INCLUDE_TCPSERVER_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <spdlog/spdlog.h>

#include "tcp_connection.hpp"
#include "connection_manager.hpp"
#include "snowflaked_service.hpp"

namespace lisea {
namespace http {

class TcpServer: public std::enable_shared_from_this<TcpServer> {

public:

    TcpServer(std::string address, unsigned short port,
            SnowflakedService &snowflaked_service) : //
            io_context(1), //
            acceptor(io_context), //
            manager(snowflaked_service), //
            LOG(spdlog::get(lisea::http::LOGGER_NAME)) {

        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address,
                std::to_string(port));

        acceptor.open(endpoint.protocol());
        acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor.bind(endpoint);
        acceptor.listen();

        do_accept();
    }

    void run();

private:
    std::shared_ptr<spdlog::logger> LOG;

    void do_accept();

    ConnectionManager manager;

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;
};

} // NS
}

#endif /* INCLUDE_TCPSERVER_H */

