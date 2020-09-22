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
#include "tcp_connection.hpp"
#include "connection_manager.hpp"

namespace lisea {
namespace http {

tcp::socket& TcpConnection::get_socket() {
    return soket;
}

void TcpConnection::start(SnowflakedService &snowService) {
    do_read(snowService);
}

void TcpConnection::stop() {
    soket.close();
}

void TcpConnection::do_read(SnowflakedService &snowService) {

    auto self(shared_from_this());
    std::string flake(std::to_string(snowService.getSnowflaked().buildGetSnowflakeId()));
    LOG->info("Created output flake: {}", flake);

    soket.async_read_some(boost::asio::buffer(in_buffer),
            [this, self, flake](boost::system::error_code ec,
                    std::size_t bytes_transfered) {

                if (!ec) {
                    RequestParser::ResultResult result;
                    parser.parse(request, in_buffer);

                    reply = Reply::business_reply(Reply::StatusType::OK,
                            lisea::http::SingleJsonValue::getSingleJsonValue(flake),
                            Reply::ContentType::JSON);

                    do_write();
                }
                else {
                    LOG->error("TcpConnection::do_read error: {}", ec.message());
                }
            });
}

void TcpConnection::do_write() {

    auto self(shared_from_this());
    boost::asio::async_write(soket, reply.to_buffers(),
            [this, self](boost::system::error_code ec, std::size_t) {

                if (!ec) {
                    LOG->debug("do write message: {}", ec.message());
                    soket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                }

                if (ec != boost::asio::error::operation_aborted) {
                    manager.stop(self);
                }
            });
}

} // namespace
} // namespace
