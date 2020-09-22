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
/**
 * based on snowflaked project created by Dwayn Matthies in 2014, which was in
 * turn based on twitter snowflake project.
 * I find snowflaked implementation to be efficient, therefore I've more or less
 * recycled the implementation, ported it to cpp.
 * DR
 *
 * snowflaked project can be found on:
 * https://github.com/dwayn/snowflaked
 *
 * twitter snowflake project can be found on:
 * https://github.com/twitter-archive/snowflake
 *
 * **/
#ifndef SNOWFLAKED_H
#define SNOWFLAKED_H

#include <spdlog/spdlog.h>
#include <stdint.h>

namespace lisea {
namespace http {

class Snowflaked {
public:
    Snowflaked(const long int &time, const long int &worker, const long int &region,
            const long int &sequence);

    int64_t buildGetSnowflakeId();

private:
    const int SNOWFLAKE_SIGN_BITS = 1;
    const int SNOWFLAKE_TIME_BITS = 41;
    const int SNOWFLAKE_REGION_BITS = 4;
    const int SNOWFLAKE_WORKER_BITS = 10;
    const int SNOWFLAKE_SEQUENCE_BITS = 8;

    long int time;
    long int worker;
    long int region;
    long int sequence;

};

}
} //NS

#endif
