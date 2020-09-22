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

#include "connection_manager.hpp"

namespace lisea {
namespace http {

//TODO handle exceptions during startup/shutdown
void ConnectionManager::start(TcpConnection::TcpConnectionPtr con_ptr) {
    LOG->debug("ConnectionManager::start from {}",
            boost::lexical_cast<std::string>(con_ptr));

    connection_set.insert(con_ptr);
    con_ptr->start(snowflaked_service);
}

void ConnectionManager::stop(TcpConnection::TcpConnectionPtr con_ptr) {
    LOG->debug("ConnectionManager::stop from  {}",
            boost::lexical_cast<std::string>(con_ptr));

    connection_set.erase(con_ptr);
    con_ptr->stop();
}

void ConnectionManager::stop_all() {
    LOG->debug("ConnectionManager::stop_all");

    std::for_each(connection_set.begin(), connection_set.end(),
            [](TcpConnection::TcpConnectionPtr con_ptr) {
                con_ptr->stop();
            });
    connection_set.clear();
}

}
} //NS
