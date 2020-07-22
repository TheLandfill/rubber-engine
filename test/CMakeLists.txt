cmake_minimum_required(VERSION 3.0.0)
set(project test)
project(${project})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(CUR_PLATFORM "${CMAKE_SOURCE_DIR}/engine/platform/${CMAKE_SYSTEM_NAME}")

include_directories(
	"${CMAKE_SOURCE_DIR}/engine/includes"
	"${CMAKE_SOURCE_DIR}/engine/"
	"${CMAKE_SOURCE_DIR}/${project}/includes"
)# ${CUR_PLATFORM}/includes)

link_directories("${CMAKE_SOURCE_DIR}/engine/${CMAKE_BUILD_TYPE}/lib/")

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/test/src/*.cpp")
message("${SOURCES}")
#file(GLOB PLATFORM_SOURCES "${CUR_PLATFORM}/src/*.cpp")
#message("${PLATFORM_SOURCES}")

add_executable("${project}" "${SOURCES}")

target_precompile_headers(engine PRIVATE ${CMAKE_SOURCE_DIR}/engine/includes/rbrpch.h)
target_link_libraries("${project}" engine)
