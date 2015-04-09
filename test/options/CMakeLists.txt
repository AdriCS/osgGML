# SOURCE: http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(OptionsTesting)

set(CMAKE_BUILD_TYPE "RELEASE")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

include_directories(../../include)
set(DEPENDENCIES ${DEPENDENCIES} ${LIBRARY_NAME})

# Hack for my weird Boost installation in Windows.
if(WIN32 AND MINGW)
    set(BOOST_ROOT "D:/PROYECTOS/SITEGI/LIBRERIAS/Boost")
	include(../../cmake/find/find_boost.cmake)
else()
	find_package(Boost REQUIRED COMPONENTS unit_test_framework)
endif()

include_directories (${Boost_INCLUDE_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${Boost_LIBRARIES})
#add_definitions(-DBOOST_TEST_DYN_LINK)
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB OpenThreads)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${OPENSCENEGRAPH_LIBRARIES})

MESSAGE(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE(STATUS "INSTALL PREFIX = ${CMAKE_INSTALL_PREFIX}")

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

set(TEST_DEST ${CMAKE_BINARY_DIR}/testBinaries)
message(STATUS "CMAKE_BINARY_DIR -> ${CMAKE_BINARY_DIR}")
message(STATUS "PROJECT_BINARY_DIR -> ${PROJECT_BINARY_DIR}")

#set(TEST_LINK_DEPS ${TEST_LINK_DEPS} "-Wl,-rpath,${CMAKE_BINARY_DIR}")
set(TEST_LINK_DEPS ${TEST_LINK_DEPS} "-Wl,-rpath,${Boost_LIBRARY_DIRS}")

message(STATUS ${TEST_LINK_DEPS})
#Run through each source
foreach(testSrc ${TEST_SRCS})
        #Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)
		
		MESSAGE(STATUS "Test file: ${testSrc} -> Test: ${testName}")

        #Add compile target
        add_executable(${testName} ${testSrc})

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(${testName} ${DEPENDENCIES})

		set_target_properties(${testName} PROPERTIES
		                      RUNTIME_OUTPUT_DIRECTORY ${TEST_DEST}
							  LINK_FLAGS "${TEST_LINK_DEPS}"
        )
			
        #Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName}
		         WORKING_DIRECTORY ${TEST_DEST}
				 COMMAND ${TEST_DEST}/${testName}
		)
endforeach(testSrc)
