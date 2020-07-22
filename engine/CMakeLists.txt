cmake_minimum_required(VERSION 3.0.0)
project(engine)

add_definitions(-DRUBBER_BUILD_DLL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(CUR_PLATFORM "${CMAKE_SOURCE_DIR}/engine/platform/${CMAKE_SYSTEM_NAME}")

include_directories(${CMAKE_SOURCE_DIR}/engine/includes)# ${CUR_PLATFORM}/includes)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/engine/src/*.cpp")
#file(GLOB PLATFORM_SOURCES "${CUR_PLATFORM}/src/*.cpp")
#message("${PLATFORM_SOURCES}")

add_library(engine SHARED "${SOURCES}")# "${PLATFORM_SOURCES}")

target_precompile_headers(engine PRIVATE ${CMAKE_SOURCE_DIR}/engine/includes/rbrpch.h)

target_link_libraries(engine)
