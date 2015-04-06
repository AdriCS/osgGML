cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Options)

set(CMAKE_BUILD_TYPE "RELEASE")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgUtil OpenThreads)
set(OpenSceneGraph_ADDITIONAL_VERSIONS "3.0.1" "3.2.1")
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
set(DEPENDENCIES ${OPENSCENEGRAPH_LIBRARIES})


include_directories(../../include)
add_library(Options ../../src/GmlOptions.cpp ../../src/GmlOptionsIO.cpp)
target_link_libraries(Options ${DEPENDENCIES})

add_executable(options_example options.cpp)
target_link_libraries(options_example Options ${DEPENDENCIES})

INSTALL(TARGETS Options options_example
        RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
INSTALL(FILES ../../include/GmlOptions.h ../../include/GmlOptionsIO.h DESTINATION include)
