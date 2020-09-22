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
#include <tcp_server.hpp>

namespace lisea {
namespace http {

//public
void TcpServer::run() {
    io_context.run();
}

void TcpServer::do_accept() {

//    auto self(shared_from_this());
    acceptor.async_accept(
            [this](boost::system::error_code const &error,
                    boost::asio::ip::tcp::socket soket_l) {

                if (error) {
                    LOG->error("TcpServer::do_accept error: {}", error.message());
                }

                if (!acceptor.is_open()) {
                    LOG->error("TcpServer::do_accept: acceptor not running! Message: {}",
                            error.message());
                    return;
                }

                if (!error) {
                    LOG->info("Accepting connection from {}",
                            soket_l.remote_endpoint().address().to_string());

                    manager.start(
                            std::make_shared<lisea::http::TcpConnection>(
                                    std::move(soket_l), manager));
                }

                do_accept();
            });
}

}
} //NS
