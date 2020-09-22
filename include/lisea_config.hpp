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
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/spdlog.h>

#ifndef INCLUDE_LISEA_CONFIG_H
#define INCLUDE_LISEA_CONFIG_H

//using Header = std::map<std::string, std::string>;

namespace lisea {
namespace http {

constexpr const int IN_BUFFER_LENGTH = 8192;
const std::string LOGGER_NAME = "VULCAN_LOGGER";

class SingleJsonValue {
public:
    static std::string getSingleJsonValue(const std::string &value) {
        return "{ \"snowflakedId\": " + value + "}";
    }
};

class LoggerConfig {
public:
    LoggerConfig() = delete;

    enum LoggingLevel {
        DEVELOPMENT, PRODUCTION
    } logging_level;

    static void setup_log_level(LoggingLevel level) {

        switch (level) {
        case DEVELOPMENT:
            return setup_dev_logging();
        case PRODUCTION:
            return setup_prod_logging();
        }

    }

private:
    static void setup_dev_logging() {
        auto log = spdlog::stdout_color_st(lisea::http::LOGGER_NAME,
                spdlog::color_mode::always);

        set_global_patter();

        log->set_level(spdlog::level::debug);
        log->flush_on(spdlog::level::debug);
    }

    static void setup_prod_logging() {

        auto log = spdlog::rotating_logger_mt(lisea::http::LOGGER_NAME, "logs/vulcan.log",
                1048576 * 5, 3);

        set_global_patter();

        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);
    }

    static void set_global_patter() {

        spdlog::set_pattern("[%D %H:%M:%S:%e] [%t] [%l] %v");
    }

};

}
} //NS

#endif /* INCLUDE_LISEA_CONFIG_H */
