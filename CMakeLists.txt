cmake_minimum_required(VERSION 3.17.3)
project (lisea_vulcan)


find_package(Boost REQUIRED)
find_package(Boost COMPONENTS thread REQUIRED)
find_package(args REQUIRED)
find_package(spdlog REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(lisea_vulcan ${SOURCES})

target_compile_features(lisea_vulcan PUBLIC cxx_std_14)

# set_target_properties(lisea_vulcan PROPERTIES CXX_EXTENSIONS OFF)
# auto select standard
# target_compile_features(lisea_vulcan PRIVATE cxx_range_for)

target_link_libraries(lisea_vulcan PRIVATE spdlog::spdlog ${Boost_LIBRARIES} )
