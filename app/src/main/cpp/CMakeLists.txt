# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("CXXLib")

# PROJECT_SOURCE_DIR = /Users/zanewang/Downloads/WorkSpace/MyGithub/Android/MyCXXApplication/app/src/main/cpp
set(TAG wzgtest)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})

include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/base)
include_directories(${SOURCE_DIR}/base/array)
include_directories(${SOURCE_DIR}/base/file)
include_directories(${SOURCE_DIR}/base/memory)
include_directories(${SOURCE_DIR}/base/object)
include_directories(${SOURCE_DIR}/base/object/bean)
include_directories(${SOURCE_DIR}/component)
include_directories(${SOURCE_DIR}/utils)

aux_source_directory(${SOURCE_DIR}/base SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/array SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/file SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/memory SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/object SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/object/bean SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/component SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/utils SOURCE_FILE)

add_library(native-lib SHARED ${SOURCE_FILE})

target_link_libraries(native-lib log android)