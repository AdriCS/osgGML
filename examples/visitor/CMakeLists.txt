cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Visitor)

option(BUILD_SHARED_LIBS "Build shared libs" ON)
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

link_directories(${CMAKE_BINARY_DIR}/lib)

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgGA
             osgText osgUtil osgViewer OpenThreads
)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
# HACK!!!! DO THIS PROPERLY!!!
link_directories(${OPENSCENEGRAPH_BINARY_DIRS}/osgPlugins-3.2.1/)
set(DEPENDENCIES ${OPENSCENEGRAPH_LIBRARIES})


include_directories(../../include)
add_library(Options ../../src/GmlOptions.cpp ../../src/GmlOptionsIO.cpp)
target_link_libraries(Options ${DEPENDENCIES})
add_library(Visitor SHARED ../../src/GraphVisitor.cpp ../../src/ReaderWriterGML.cpp)
target_link_libraries(Visitor Options ${DEPENDENCIES})

add_executable(visitor_example visitor.cpp)
target_link_libraries(visitor_example Options Visitor ${DEPENDENCIES})

INSTALL(TARGETS Options Visitor visitor_example
        RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
INSTALL(FILES cessna.osg DESTINATION bin)
INSTALL(DIRECTORY ../../include DESTINATION ${CMAKE_INSTALL_PREFIX})
