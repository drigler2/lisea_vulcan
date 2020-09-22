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
#include <snowflaked_service.hpp>

namespace lisea {
namespace http {

// public static
SnowflakedService& SnowflakedService::get_instance(const int worker, const int region) {

    spdlog::get("VULCAN_LOGGER")->debug("Instantiating SnowflakedService....");
    static SnowflakedService instance = SnowflakedService(worker, region);

    return instance;
}

// public
Snowflaked SnowflakedService::getSnowflaked() {

    this->updateTime();
//	this->updateTime2();

    if (this->time == time) {
        this->sequence++;
    }

    return Snowflaked(this->time, this->worker, this->region, this->sequence);
}

// private
SnowflakedService::SnowflakedService(const int &worker, const int &region) {
    this->time = 0l;
    this->worker = worker;
    this->region = region;
    this->sequence = 0;
}
;

void SnowflakedService::updateTime() {

    long int ms;
    {
        using namespace std::chrono;
        ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
    this->time = ms;
}

/**
 * Possibly not entirely accurate, not clear if this influences the ordering of id-s.
 * Use with caution
 *
 * **/
void SnowflakedService::updateTime2() {

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    this->time = ms;
}

}
} //NS
