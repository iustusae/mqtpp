cmake_minimum_required(VERSION 3.25.1)

project(mqt VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/usr/local/include ${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hpp")

add_executable(mqt ${SOURCES} ${HEADERS} src/Backend/util.cpp src/Backend/util.h src/Backend/Model/Unit.h src/Backend/MongoDBManager.cpp)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
find_package(Boost REQUIRED)

target_link_libraries(mqt mongo::mongocxx_shared mongo::bsoncxx_shared ${Boost_LIBRARIES})