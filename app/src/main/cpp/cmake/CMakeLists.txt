# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("CXXApplication")

set(TAG wzgtest)
# 设置一些常用变量
# NDK 目录路径
set(CMAKE_ANDROID_NDK /Users/zanewang/Downloads/WorkSpace/SDK/Android-NDK/android-ndk-r14b)
set(CMAKE_PROGRAM_PATH /Users/zanewang/Downloads/WorkSpace/MyGithubs/Android/MyCXXApplication/app)

#有序性，定义方法须放在前面
FUNCTION(log tag message)
    message(${${tag}}:\  ${${message}})
endfunction()

#常用的常量
log(TAG CMAKE_APPBUNDLE_PATH)
log(TAG CMAKE_CURRENT_SOURCE_DIR) # /Users/zanewang/Downloads/WorkSpace/MyGithubs/Android/MyCXXApplication/app/src/main/cpp/cmake
log(TAG CMAKE_PROGRAM_PATH)
log(TAG CMAKE_MODULE_PATH)

include_directories(${CMAKE_PROGRAM_PATH}/prebuild/libyuv/include)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)
find_library(android-lib android) # 使用 native window

add_library(libyuv SHARED IMPORTED)
set_target_properties(libyuv # Specifies the target library.
        # Specifies the parameter you want to define.
        PROPERTIES IMPORTED_LOCATION
        # Provides the path to the library you want to import.
        ${CMAKE_PROGRAM_PATH}/prebuild/libyuv/libs/${ANDROID_ABI}/libyuv_ttt.so
        )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

add_library(native-lib # Sets the name of the library.
        SHARED  # Sets the library as a shared library.
        # Provides a relative path to your source file(s).
        ../base/BaseObject.cpp
        ../base/ChildObject.cpp
        ../base/BaseTypeTest.cpp
        ../base/ByteBufferTest.cpp
        ../base/JniTransDataTest.cpp
        ../base/CollectionTest.cpp
        ../base/StringTest.cpp
        ../base/PointerTest.cpp
        ../base/MemoryTest.cpp
        ../utils/TimeUtils.cpp
        ../utils/ThreadUtils.cpp
        ../Common.cpp
        ../native-lib.cpp)

target_link_libraries(native-lib # Specifies the target library.
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${android-lib}
        libyuv)