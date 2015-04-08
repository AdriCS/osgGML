cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Visitor)

option(BUILD_SHARED_LIBS "Build shared libs" ON)
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${osgGML_INCLUDE_DIRS})
link_directories(${osgGML_LIBRARY_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${osgGML_LIBRARIES})

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgGA
             osgText osgUtil osgViewer OpenThreads
)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
# HACK!!!! DO THIS PROPERLY!!!
link_directories(${OPENSCENEGRAPH_BINARY_DIRS}/osgPlugins-3.2.1/)
set(DEPENDENCIES ${OPENSCENEGRAPH_LIBRARIES})

add_executable(visitor_example visitor.cpp)
target_link_libraries(visitor_example ${DEPENDENCIES})

INSTALL(TARGETS visitor_example
        RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
INSTALL(FILES cessna.osg DESTINATION bin)
