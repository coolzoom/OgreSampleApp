cmake_minimum_required(VERSION 3.7.2)

################################################################################
project (OGRE_SAMPLE_APP)
# Juan Maria Gomez Lopez juanecitorr@gmail.com

################################################################################

set (CMAKE_CXX_STANDARD 11)

set( PROJECT_SOURCE_DIR ./src)
set( PROJECT_BINARY_DIR ./include)



# Get the OGRE_HOME environment variable with unix slashes
set(OGRE_HOME "$ENV{OGRE_HOME}")
set(OGRE_DIR "${OGRE_HOME}/CMake")

STRING(REGEX REPLACE "\\\\" "/" OGRE_HOME ${OGRE_HOME})
# Copy Media and Bin folders out to the repository
file(COPY ${OGRE_HOME}/bin DESTINATION ${CMAKE_SOURCE_DIR})
file(COPY ${OGRE_HOME}/media DESTINATION ${CMAKE_SOURCE_DIR})

# specify which version and components you need
find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)
 

# Add configs to the source grouping for Visual Studio
if(MSVC)
    file(GLOB PROJECT_CONFIGS_WINDOWS_RELEASE src/config/windows/release/*.cfg)

    source_group("Configs\\Windows_Configs\\Release" FILES ${PROJECT_CONFIGS_WINDOWS_RELEASE})
	
	# copy resource.cfg next to our binaries where OGRE looks for it
	file(COPY ${PROJECT_CONFIGS_WINDOWS_RELEASE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	 
endif(MSVC)


# Support C++11
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags
# -w Disables all warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# set( MY_OGRE_DIR ~/git/ogre)
# set( MY_OGRE_DIR C:/Users/Administrator/Downloads/ogre-sdk-master2-vc15-x64)

# The version number.
set (OGRE_SAMPLE_APP_VERSION_MAJOR 1)
set (OGRE_SAMPLE_APP_VERSION_MINOR 0)

################################################################################
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/OgreSampleAppConfig.h.in"
  "${PROJECT_BINARY_DIR}/OgreSampleAppConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find OgreSampleAppConfig.h
include_directories("${PROJECT_BINARY_DIR}")

################################################################################
include_directories ("${OGRE_HOME}/include"
                        "${OGRE_HOME}/include/OGRE"
						"${OGRE_HOME}/include/OGRE/RTShaderSystem"
						"${OGRE_HOME}/include/OGRE/Bites"
						"${OGRE_HOME}/include/OGRE/Overlay"
						./include)

################################################################################
# add libraries directories
# link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${OGRE_HOME}/lib)

################################################################################
# add libraries
# add_library( )



################################################################################
# add executable
add_executable(ogre_sample_app 
	src/main.cpp 
	src/ogre_sample_app.cpp
	${PROJECT_CONFIGS_WINDOWS_RELEASE}
	)
	# Output to bin directory

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries (ogre_sample_app OgreMain OgreBites OgreRTShaderSystem)




