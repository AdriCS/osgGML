cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Options)

set(CMAKE_BUILD_TYPE "RELEASE")

find_package(osgGML REQUIRED)
if(osgGML_FOUND)
	message(STATUS "OSG GML WAS FOUND")
	message(STATUS "INCDIR: ${osgGML_INCLUDE_DIRS}")
	message(STATUS "LIBDIR: ${osgGML_LIBRARY_DIRS}")
	message(STATUS "LIB   : ${osgGML_LIBRARIES}")
endif()
include_directories(${osgGML_INCLUDE_DIRS})
link_directories(${osgGML_LIBRARY_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${osgGML_LIBRARIES})

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB OpenThreads)
set(OpenSceneGraph_ADDITIONAL_VERSIONS "3.0.1" "3.2.1")
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${OPENSCENEGRAPH_LIBRARIES})
message(STATUS ${DEPENDENCIES})

add_executable(options_example options.cpp)
target_link_libraries(options_example ${DEPENDENCIES})

install(TARGETS options_example
        RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
