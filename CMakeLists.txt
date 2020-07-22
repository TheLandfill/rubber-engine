cmake_minimum_required(VERSION 3.0.0)
project(rubber-engine)

set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/engine/vendors/)
include_directories(
	${CMAKE_SOURCE_DIR}/engine/
	${CMAKE_SOURCE_DIR}/engine/includes/
	${CMAKE_SOURCE_DIR}/engine/vendors/includes/
)
file(GLOB VENDOR_LIBRARY_DIRS "${VENDOR_DIR}/libs/*")
link_directories("${VENDOR_LIBRARY_DIRS}")

add_subdirectory(engine)
add_subdirectory(test)
