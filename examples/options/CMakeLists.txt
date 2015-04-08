cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Options)

set(CMAKE_BUILD_TYPE "RELEASE")

include_directories(../../include)
set(DEPENDENCIES ${DEPENDENCIES} ${LIBRARY_NAME})

find_package(OpenSceneGraph REQUIRED COMPONENTS
               osg
			   osgDB
			   OpenThreads
)
set(OpenSceneGraph_ADDITIONAL_VERSIONS "3.0.1" "3.2.1")
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${OPENSCENEGRAPH_LIBRARIES})

add_executable(options_example options.cpp)
target_link_libraries(options_example ${DEPENDENCIES})

install(TARGETS options_example
        RUNTIME DESTINATION ${OSGGML_EXAMPLES_BIN_DIR}
)
