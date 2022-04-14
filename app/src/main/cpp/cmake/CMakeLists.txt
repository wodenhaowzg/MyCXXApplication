# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("CXXLib")

# PROJECT_SOURCE_DIR = /Users/zanewang/Downloads/WorkSpace/MyGithub/Android/MyCXXApplication/app/src/main/cpp/cmake
set(TAG wzgtest)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/..)

include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/utils)
include_directories(${SOURCE_DIR}/base)
include_directories(${SOURCE_DIR}/base/object)
include_directories(${SOURCE_DIR}/component)
include_directories(${SOURCE_DIR}/component/thread)

aux_source_directory(${SOURCE_DIR} SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/utils SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/object SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/component SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/component/thread SOURCE_FILE)

add_library(native-lib SHARED ${SOURCE_FILE})

target_link_libraries(native-lib log android)