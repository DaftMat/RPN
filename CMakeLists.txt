cmake_minimum_required(VERSION 3.03)
project(RPN)

set(CMAKE_CXX_STANDARD 14)

# set the environment variables
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RPN_BUNDLE ${CMAKE_CURRENT_SOURCE_DIR}/Bundle-${CMAKE_CXX_COMPILER_ID})
set(RPN_3RDPARTY ${CMAKE_CURRENT_SOURCE_DIR}/3rdPartyLibs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${RPN_BUNDLE}/bin)
set(EXECUTABLE_OUTPUT_PATH          ${RPN_BUNDLE}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${RPN_BUNDLE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${RPN_BUNDLE}/lib)
set(RPN_INCLUDE_DIR ${CMAKE_SOURCE_DIR})

if ( NOT CMAKE_PREFIX_PATH )
    set( CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
endif()

# guard against in-source builds (source: Eigen)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# get the RPN library sources
file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_SOURCE_DIR}/*.hpp ${CMAKE_SOURCE_DIR}/*.h)
file(GLOB_RECURSE inlines ${CMAKE_SOURCE_DIR}/*.inl)

# compile library
add_library(${CMAKE_PROJECT_NAME} SHARED ${sources} ${headers} ${inlines})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# compile application and tests
add_subdirectory(application)
add_subdirectory(test EXCLUDE_FROM_ALL)