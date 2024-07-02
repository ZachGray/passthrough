#-
# ==========================================================================
# Copyright (c) 2018 Autodesk, Inc.
# All rights reserved.
# 
# These coded instructions, statements, and computer programs contain
# unpublished proprietary information written by Autodesk, Inc., and are
# protected by Federal copyright law. They may not be disclosed to third
# parties or copied or duplicated in any form, in whole or in part, without
# the prior written consent of Autodesk, Inc.
# ==========================================================================
#+


cmake_minimum_required(VERSION 3.13)

# Project setup
project(passThroughNode
    VERSION 2.0
    DESCRIPTION "test"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


# Set default MAYAVERSION if not defined
if(NOT DEFINED ENV{MAYAVERSION})
    set(ENV{MAYAVERSION} 2025)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(NOT DEFINED ENV{DEVKIT_LOCATION})
        set(ENV{DEVKIT_LOCATION} "Z:/devkits/$ENV{MAYAVERSION}/devkitBase")
    endif()
endif()


# include the project setting file
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)



# specify project name
set(PROJECT_NAME passThroughNode)


# set SOURCE_FILES
set(SOURCE_FILES
   passThroughNode.cpp
)

# set linking libraries
set(LIBRARIES
     OpenMaya
     Foundation

)





# Build plugin
build_plugin()

