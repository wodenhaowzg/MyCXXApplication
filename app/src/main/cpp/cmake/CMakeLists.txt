# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 为所有 c/c++ 编译器设置编译选项，可以把公用的选项放到这里，只能设置一次，不能重复设置，后者会覆盖前者
#add_compile_options("-frtti -fexceptions")
# 为 c++ 编译器设置编译选项，只能设置一次，不能重复设置，后者会覆盖前者
set(CMAKE_CXX_FLAGS "-std=c++11 -w -frtti -fexceptions")
# 为 c 编译器设置编译选项，只能设置一次，不能重复设置，后者会覆盖前者
set(CMAKE_C_FLAGS "-w")
set(CMAKE_ANDROID_NDK /Users/zanewang/Downloads/WorkSpace/SDK/Android-NDK/android-ndk-r14b)
#set(CMAKE_INCLUDE_PATH )

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ../base/BaseObject.cpp
        ../base/ChildObject.cpp
        ../utils/TimeUtils.cpp
        ../utils/ThreadUtils.cpp
        ../Common.cpp
        ../native-lib.cpp)

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

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})