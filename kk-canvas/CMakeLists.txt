
cmake_minimum_required(VERSION 3.4.1)

add_library(duktape
            SHARED
            IMPORTED)

set_target_properties(duktape
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/lib/${ANDROID_ABI}/libduktape.so)

add_library(event
            SHARED
            IMPORTED)

set_target_properties(event
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/lib/${ANDROID_ABI}/libevent.so)

add_subdirectory(kk-object)
add_subdirectory(kk-element)


add_library(kk-canvas
            SHARED
            src/main/jni/kk.c
            src/main/jni/src/kk-canvas.cc
            src/main/jni/src/CGContext.cc
            src/main/jni/src/CGContextJS.cc
            src/main/jni/src/WebGLContext.cc
            src/main/jni/src/WebGLContextJS.cc
            src/main/jni/CGContext.cc
            src/main/jni/CGImage.cc
            src/main/jni/kk-canvas.cc
            )

include_directories(
            src/main/jni/include
            src/main/jni/js
            src/main/jni/duktape
            src/main/jni/md5
            src/main/jni/
            src/main/jni/libevent/include
            src/main/jni/kk-object/include
            src/main/jni/kk-element/include
            )

set_target_properties(kk-canvas PROPERTIES
    CXX_STANDARD 11
)

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries(
                    kk-canvas
                    kk-element
                    kk-object
                    duktape
                    event
                    android
                    z
                    GLESv2
                    EGL
                    log
                    )
