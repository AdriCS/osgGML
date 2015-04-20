# Base build for the library.

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(osgGML)

message(STATUS "${PROJECT_SOURCE_DIR}")

option(BUILD_SHARED_LIBS "Build shared libs" ON)
option(BUILD_EXAMPLES OFF)
option(BUILD_TESTS OFF)
option(BUILD_USE_LAMBDAS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(LIBRARY_NAME "osgGML")
set(EXPORT_NAME "depends")
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "" FORCE)
set(CMAKE_COLOR_MAKEFILE ON)
mark_as_advanced(CMAKE_VERBOSE_MAKEFILE)

 # Common locatoins for Unix and Mac OS X
set(DEFAULT_BIN_SUBDIR bin)
set(DEFAULT_LIB_SUBDIR lib)
set(DEFAULT_SHARE_SUBDIR share/cmake)
set(DEFAULT_INCLUDE_SUBDIR include)
set(OSGGML_BIN_SUBDIR ${DEFAULT_BIN_SUBDIR} CACHE STRING
"Subdirectory where executables will be installed")
set(OSGGML_LIB_SUBDIR ${DEFAULT_LIB_SUBDIR} CACHE STRING
"Subdirectory where libraries will be installed")
set(OSGGML_INCLUDE_SUBDIR ${DEFAULT_INCLUDE_SUBDIR} CACHE STRING
"Subdirectory where header files will be installed")
set(OSGGML_SHARE_SUBDIR ${DEFAULT_SHARE_SUBDIR} CACHE STRING
"Subdirectory where data will be installed")

# Full paths for the installation
set(OSGGML_BIN_DIR ${OSGGML_BIN_SUBDIR})
set(OSGGML_LIB_DIR ${OSGGML_LIB_SUBDIR})
set(OSGGML_INCLUDE_DIR ${OSGGML_INCLUDE_SUBDIR})
set(OSGGML_SHARE_DIR ${OSGGML_SHARE_SUBDIR})

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

if(BUILD_USE_LAMBDAS)
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
endif()

find_package(OpenSceneGraph REQUIRED COMPONENTS
                 osg
				 osgDB
				 OpenThreads
)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
# HACK!!!! DO THIS PROPERLY!!!
link_directories(${OPENSCENEGRAPH_BINARY_DIRS}/osgPlugins-3.2.1/)
set(DEPENDENCIES ${OPENSCENEGRAPH_LIBRARIES})

##
set(osgGML_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
set(osgGML_SOURCE_DIRS "${PROJECT_SOURCE_DIR}/src")

set(HEADERS ${osgGML_INCLUDE_DIRS}/DebugUtils.h
            ${osgGML_INCLUDE_DIRS}/GmlOptions.h
			${osgGML_INCLUDE_DIRS}/GmlOptionsIO.h
			${osgGML_INCLUDE_DIRS}/GraphVisitor.h
			${osgGML_INCLUDE_DIRS}/ReaderWriterGML.h
			${osgGML_INCLUDE_DIRS}/Setup.h
)
set(SOURCES ${osgGML_SOURCE_DIRS}/GmlOptions.cpp
            ${osgGML_SOURCE_DIRS}/GmlOptionsIO.cpp
			${osgGML_SOURCE_DIRS}/GraphVisitor.cpp
			${osgGML_SOURCE_DIRS}/ReaderWriterGML.cpp
)
include_directories(${osgGML_INCLUDE_DIRS})
add_library(${LIBRARY_NAME} ${SOURCES})
target_link_libraries(${LIBRARY_NAME} ${DEPENDENCIES})

#
install(TARGETS ${LIBRARY_NAME}
        EXPORT ${EXPORT_NAME}
        RUNTIME DESTINATION ${OSGGML_BIN_DIR}
		LIBRARY DESTINATION ${OSGGML_LIB_DIR}
		ARCHIVE DESTINATION ${OSGGML_LIB_DIR}
)
install(FILES ${HEADERS} DESTINATION ${OSGGML_INCLUDE_DIR})

if(BUILD_EXAMPLES)
  message(STATUS "Building EXAMPLES.")
  set(OSGGML_EXAMPLES_BIN_DIR share/examples)
  add_subdirectory(examples/options)
  add_subdirectory(examples/visitor)
endif()

if(BUILD_TESTS)
  enable_testing()

  message(STATUS "Building TESTS")
  
  set(OSGGML_TESTS_BIN_DIR share/tests)
  # :TODO: Create a SHARED TEST CMakeLists, to search for Boost and set paths...
  add_subdirectory(test/options)
endif()

###########

add_subdirectory(cmake/conf)

###########
