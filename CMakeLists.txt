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
#				 osgGA
#				 osgText
#				 osgUtil
#                 osgViewer
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
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
		LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

###########

set(CMAKE_DEST_DIR "share/cmake")
set(PROJECT_ROOT_DIR "../..")
configure_file("cmake/${PROJECT_NAME}-config.cmake.in" ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake @ONLY)


message(STATUS "IN CONFIG.IN CURRENT LIST -> ${CMAKE_CURRENT_LIST_FILE}")
message(STATUS "IN CONFIG.IN PROJECT ROOT -> ${PROJECT_ROOT_DIR}")


install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
              DESTINATION "${CMAKE_DEST_DIR}"
)
install(EXPORT ${EXPORT_NAME} FILE "${PROJECT_NAME}-${EXPORT_NAME}.cmake"
        DESTINATION "${CMAKE_DEST_DIR}"
)