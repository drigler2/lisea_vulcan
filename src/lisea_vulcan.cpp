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
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>

#include "lisea_config.hpp"
#include "snowflaked_service.hpp"
#include "tcp_server.hpp"

static lisea::http::LoggerConfig::LoggingLevel selectLogLevel(int argc, char *argv[]);
static void printLiseaArt(std::shared_ptr<spdlog::logger> LOG);

int main(int argc, char *argv[]) {

    try {
        lisea::http::LoggerConfig::setup_log_level(selectLogLevel(argc, argv));
    }
    catch (std::invalid_argument &e) {
        return 1;
    }

    auto LOG = spdlog::get(lisea::http::LOGGER_NAME);
    printLiseaArt(LOG);

    std::string host("127.0.0.1");
    int port(8080);

    try {
        LOG->info("Welcome to Lisea Vulcan! Running server on host: {}, port {}", host,
                port);

        lisea::http::TcpServer server(host, port,
                lisea::http::SnowflakedService::get_instance(0, 0));
        server.run();
    }
    catch (std::exception &e) {
        LOG->error("Encountered an error in main: {}", e.what());
    }

    return 0;
}

static lisea::http::LoggerConfig::LoggingLevel selectLogLevel(int argc, char *argv[]) {
    if (argc == 2) {
        std::vector<std::string> args(argv + 1, argv + argc);

        if (args[0] == "dev") {
            return lisea::http::LoggerConfig::DEVELOPMENT;
        }
        else if (args[0] == "prod") {
            return lisea::http::LoggerConfig::PRODUCTION;
        }
        else {
            std::cout << args[0]
                    << " is incorrect profile, supported profiles are \"dev\" or \"prod\""
                    << std::endl;
            throw new std::invalid_argument("Incorrect number of arguments");
        }
    }
    else {
        std::cout << "Supported number of args is 1! eg: lisea_vulcan dev" << std::endl;
        throw new std::invalid_argument("Incorrect profile selected");
    }

}

static void printLiseaArt(std::shared_ptr<spdlog::logger> LOG) {

    if (LOG->level() == spdlog::level::info) {

        std::ifstream file("src/logo.txt");

        if (!file && !file.is_open()) {
            LOG->error("Logo art file not found... skipping");
            return;
        }
        std::stringstream art;
        art << file.rdbuf();

        LOG->info(art.str());
    }
}
