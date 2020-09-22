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
#ifndef SRC_CONNECTION_MANAGER_HPP
#define SRC_CONNECTION_MANAGER_HPP

#include <set>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "tcp_connection.hpp"
#include "snowflaked_service.hpp"

namespace lisea {
namespace http {

class ConnectionManager {
public:
    ConnectionManager(SnowflakedService &snowflaked_service) :
            LOG(spdlog::get(lisea::http::LOGGER_NAME)), //
            snowflaked_service(snowflaked_service) {

    }

    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    void start(TcpConnection::TcpConnectionPtr con_ptr);
    void stop(TcpConnection::TcpConnectionPtr con_ptr);
    void stop_all();

private:
    std::shared_ptr<spdlog::logger> LOG;

    SnowflakedService &snowflaked_service;

    std::set<TcpConnection::TcpConnectionPtr> connection_set;

};

}
} //NS

#endif /* SRC_CONNECTION_MANAGER_HPP */
