cmake_minimum_required(VERSION 3.7.2)

################################################################################
project (OGRE_SAMPLE_APP)
# Juan Maria Gomez Lopez juanecitorr@gmail.com

################################################################################

set (CMAKE_CXX_STANDARD 11)

set( PROJECT_SOURCE_DIR ./src)
set( PROJECT_BINARY_DIR ./include)

# set( MY_OGRE_DIR ~/git/ogre)
set( MY_OGRE_DIR ~/git/my_ogre)

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
include_directories ("${MY_OGRE_DIR}/build/include"
						"${MY_OGRE_DIR}/OgreMain/include"
						"${MY_OGRE_DIR}/Components/RTShaderSystem/include"
						"${MY_OGRE_DIR}/Components/Bites/include"
						"${MY_OGRE_DIR}/Components/Overlay/include"
						"${MY_OGRE_DIR}/Components/RTShaderSystem/include"
						./include)

################################################################################
# add libraries directories
# link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${MY_OGRE_DIR}/build/lib)

################################################################################
# add libraries
# add_library( )



################################################################################
# add executable
add_executable(ogre_sample_app src/main.cpp src/ogre_sample_app.cpp)
target_link_libraries (ogre_sample_app OgreMain OgreBites OgreRTShaderSystem)




