project(armory)
cmake_minimum_required(VERSION 2.6)

include($ENV{WMV_BASE_PATH}/src/cmake/common.cmake)

message(STATUS "Building armory importer")

find_package(wxWidgets REQUIRED net core)
include(${wxWidgets_USE_FILE})
include_directories(${wxWidgets_INCLUDE_DIRS})

# Qt5 stuff
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_definitions(-DQT_PLUGIN)

set(src ArmoryImporter.cpp 
        jsonreader.cpp
        jsonval.cpp
        jsonwriter.cpp)

set(useful_files armoryimporter.json)
set_source_files_properties(${useful_files} PROPERTIES HEADER_FILE_ONLY TRUE)

use_core()
use_wow()
use_wxwidgets()

add_library(armory SHARED ${src} ${useful_files})
set_property(TARGET armory PROPERTY FOLDER "plugins")

target_link_libraries(armory ${wxWidgets_LIBRARIES} core wow Qt5::Core)

if(WIN32)
  install(TARGETS armory RUNTIME DESTINATION "$ENV{WMV_BASE_PATH}/bin/plugins")
endif(WIN32)


        