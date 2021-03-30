cmake_minimum_required(VERSION 3.4.1)

# 定义项目名
project("CXXApplication")

set(TAG wzgtest)
# 为所有 c/c++ 编译器设置编译选项，可以把公用的选项放到这里，只能设置一次，不能重复设置，后者会覆盖前者
#add_compile_options("-frtti -fexceptions")
# 为 c++ 编译器设置编译选项，只能设置一次，不能重复设置，后者会覆盖前者
set(CMAKE_CXX_FLAGS "-std=c++11 -w -frtti -fexceptions")
# 为 c 编译器设置编译选项，只能设置一次，不能重复设置，后者会覆盖前者
set(CMAKE_C_FLAGS "-w")

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
        ../base/ByteBufferTest.cpp
        ../utils/TimeUtils.cpp
        ../utils/ThreadUtils.cpp
        ../Common.cpp
        ../base/JniTransDataTest.cpp
        ../base/MemoryTest.cpp
        ../native-lib.cpp)

target_link_libraries(native-lib # Specifies the target library.
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${android-lib}
        libyuv)
