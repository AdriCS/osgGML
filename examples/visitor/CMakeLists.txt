cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Visitor)

set(CMAKE_BUILD_TYPE "RELEASE")

include_directories(../../include)
set(DEPENDENCIES ${DEPENDENCIES} ${LIBRARY_NAME})

find_package(OpenSceneGraph REQUIRED COMPONENTS
                osg
				osgDB
				osgGA
                osgText
				osgUtil
				osgViewer
				OpenThreads
)
set(OpenSceneGraph_ADDITIONAL_VERSIONS "3.0.1" "3.2.1")
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
# HACK!!!! DO THIS PROPERLY!!!
link_directories(${OPENSCENEGRAPH_BINARY_DIRS}/osgPlugins-3.2.1/)
set(DEPENDENCIES ${DEPENDENCIES} ${OPENSCENEGRAPH_LIBRARIES})

add_executable(visitor_example visitor.cpp)
target_link_libraries(visitor_example ${DEPENDENCIES})

install(TARGETS visitor_example
        RUNTIME DESTINATION ${OSGGML_EXAMPLES_BIN_DIR}
)
install(FILES cessna.osg DESTINATION ${OSGGML_EXAMPLES_BIN_DIR})
