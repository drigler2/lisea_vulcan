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
#include <snowflaked.hpp>

namespace lisea {
namespace http {

// public
Snowflaked::Snowflaked(const long int &time, const long int &worker,
        const long int &region, const long int &sequence) {
    this->time = time;
    this->worker = worker;
    this->region = region;
    this->sequence = sequence;
}

int64_t Snowflaked::buildGetSnowflakeId() {
    int64_t id = 0L;

    id = (this->time << this->SNOWFLAKE_TIME_BITS)
            | (this->region << this->SNOWFLAKE_SEQUENCE_BITS)
            | (this->worker << this->SNOWFLAKE_WORKER_BITS) | (this->sequence);

    return id;
}

}
} //NS
