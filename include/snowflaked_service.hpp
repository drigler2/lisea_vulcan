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
#ifndef SNOWFLAKED_SERVICE_H
#define SNOWFLAKED_SERVICE_H

#include <snowflaked.hpp>
#include <stdint.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <sys/time.h>

namespace lisea {
namespace http {

class SnowflakedService: public std::enable_shared_from_this<SnowflakedService> {
public:
    Snowflaked getSnowflaked();

    // singleton
    static SnowflakedService& get_instance(const int worker, const int region);

private:
    // members
    long int time;
    int worker;
    int region;
    int sequence;

    // constructors
    SnowflakedService(const int &worker, const int &region);
    SnowflakedService(SnowflakedService&&);

    // member functions
    void updateTime();
    void updateTime2();

    // singleton
    SnowflakedService() = default;
    ~SnowflakedService() = default;

    SnowflakedService(const SnowflakedService&) = delete;
    SnowflakedService& operator=(const SnowflakedService&) = delete;
    SnowflakedService& operator=(SnowflakedService&&) = delete;
};

}
// NS
}// NS

#endif

