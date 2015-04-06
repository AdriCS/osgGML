# Base build for the library.

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(osgGML)

option(BUILD_SHARED_LIBS "Build shared libs" ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(LIBRARY_NAME "osgGML")
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

##
# Set the build postfix extension according to what configuration is being built.
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

if(CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
elseif(CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
elseif(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
else()
  set(CMAKE_BUILD_POSTFIX "")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

option(USE_LAMBDAS OFF)
if(USE_LAMBDAS)
  # add_definitions(-DUSE_LAMBDAS) # NOPE. I already do this in 'Setup.h' if there is support for C++0x
  # Compiler-specific C++11 activation.
	if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
		execute_process(
			COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
		if((GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
	      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		else()
	      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
		endif()
	endif()
endif(USE_LAMBDAS)

find_package(OpenSceneGraph REQUIRED COMPONENTS
                 osg
				 osgDB
				 osgGA
				 osgText
				 osgUtil
                 osgViewer
				 OpenThreads
)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
# HACK!!!! DO THIS PROPERLY!!!
link_directories(${OPENSCENEGRAPH_BINARY_DIRS}/osgPlugins-3.2.1/)
set(DEPENDENCIES ${OPENSCENEGRAPH_LIBRARIES})

##

include_directories(./include)
add_library(${LIBRARY_NAME} ./src/GmlOptions.cpp
                   ./src/GmlOptionsIO.cpp
                   ./src/GraphVisitor.cpp
				   ./src/ReaderWriterGML.cpp
)
target_link_libraries(${LIBRARY_NAME} ${DEPENDENCIES})

INSTALL(TARGETS ${LIBRARY_NAME}
        RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
INSTALL(DIRECTORY ./include DESTINATION ${CMAKE_INSTALL_PREFIX})
