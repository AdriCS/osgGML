cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(OptionsTesting)

enable_testing()

MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

set(CMAKE_BUILD_TYPE "RELEASE")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

set(BOOST_ROOT "D:/PROYECTOS/SITEGI/LIBRERIAS/Boost")

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})
set(DEPENDENCIES ${Boost_LIBRARIES})
#add_definitions(-DBOOST_TEST_DYN_LINK)
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgUtil OpenThreads)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
set(DEPENDENCIES ${DEPENDENCIES} ${OPENSCENEGRAPH_LIBRARIES})

# Should do first the CMakeLists for the plugin, instead of building it everytime.
# THIS IS THE NEXT THING TO DO, but for now I just want to check if the tests
# work.
include_directories(../../include)
include_directories(../../src)


#add_executable(testOptions testOptions.cpp)
#target_link_libraries(testOptions ${DEPENDENCIES})

#Run through each source
foreach(testSrc ${TEST_SRCS})
        #Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)
		
		MESSAGE(STATUS "Test file: ${testSrc} -> Test: ${testName}")

        #Add compile target
        add_executable(${testName} ${testSrc})

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(${testName} ${DEPENDENCIES})

        #Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName} COMMAND ${testName})
endforeach(testSrc)