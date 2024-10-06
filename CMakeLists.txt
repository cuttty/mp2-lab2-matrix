cmake_minimum_required(VERSION 3.10)
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Debug' as none was specified.")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
			"MinSizeRel" "RelWithDebInfo")
endif()
option(BUILD_SAMPLES ON)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME})

include(CTest)
enable_testing()  # defines BUILD_TESTING

set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_CUSTOM_PROJECT "${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(include)

if(BUILD_SAMPLES)
	add_subdirectory(samples)
endif()

if(BUILD_TESTING)
    add_subdirectory(gtest)
	add_subdirectory(test)
endif()


# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")
