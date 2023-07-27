# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("CXXLib")

# PROJECT_SOURCE_DIR = /Users/zanewang/Downloads/WorkSpace/MyGithub/Android/MyCXXApplication/app/src/main/cpp
set(TAG wzgtest)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/../../../thirdparty)
set(LIBRARY_NAME native_lib)

include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/base)
include_directories(${SOURCE_DIR}/base/array)
include_directories(${SOURCE_DIR}/base/file)
include_directories(${SOURCE_DIR}/base/memory)
include_directories(${SOURCE_DIR}/base/object)
include_directories(${SOURCE_DIR}/base/object/bean)
include_directories(${SOURCE_DIR}/component)
include_directories(${SOURCE_DIR}/component/thread)
include_directories(${SOURCE_DIR}/utils)

aux_source_directory(${SOURCE_DIR} SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/array SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/file SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/memory SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/object SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/object/bean SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/base/transfer SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/component SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/component/thread SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/utils SOURCE_FILE)
aux_source_directory(${SOURCE_DIR}/thirdparty SOURCE_FILE)

#libyuv
include_directories(${THIRD_PARTY_DIR}/libyuv/include)
add_library(libyuv_ttt SHARED IMPORTED)
set_target_properties(libyuv_ttt PROPERTIES IMPORTED_LOCATION ${THIRD_PARTY_DIR}/libs/${ANDROID_ABI}/libyuv_ttt.so)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILE})
target_link_libraries(${LIBRARY_NAME} libyuv_ttt log android)