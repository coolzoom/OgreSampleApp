cmake_minimum_required(VERSION 3.7.2)

################################################################################
project (OGRE_SAMPLE_APP)
# Juan Maria Gomez Lopez juanecitorr@gmail.com

################################################################################

set (CMAKE_CXX_STANDARD 11)

set( PROJECT_SOURCE_DIR ./src)
set( PROJECT_BINARY_DIR ./include)

set(OGRE_DIR C:/Users/Administrator/Downloads/ogre-sdk-master2-vc15-x64/CMake)

# specify which version and components you need
find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)
 
# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
 


# set( MY_OGRE_DIR ~/git/ogre)
set( MY_OGRE_DIR C:/Users/Administrator/Downloads/ogre-sdk-master2-vc15-x64)

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
include_directories ("${MY_OGRE_DIR}/include"
                        "${MY_OGRE_DIR}/include/OGRE"
						"${MY_OGRE_DIR}/include/OGRE/RTShaderSystem"
						"${MY_OGRE_DIR}/include/OGRE/Bites"
						"${MY_OGRE_DIR}/include/OGRE/Overlay"
						./include)

################################################################################
# add libraries directories
# link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${MY_OGRE_DIR}/lib)

################################################################################
# add libraries
# add_library( )



################################################################################
# add executable
add_executable(ogre_sample_app src/main.cpp src/ogre_sample_app.cpp)
SET(EXECUTABLE_OUTPUT_PATH ${MY_OGRE_DIR}/bin) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MY_OGRE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${MY_OGRE_DIR}/bin)
target_link_libraries (ogre_sample_app OgreMain OgreBites OgreRTShaderSystem)




