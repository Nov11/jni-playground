cmake_minimum_required(VERSION 3.14)
project(native VERSION  1.0.0 DESCRIPTION "jni examples")

set(CMAKE_CXX_STANDARD 14)

add_library(native SHARED
        src/pkg_HelloJNI.cpp
        )

set_target_properties(native PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(native PROPERTIES PUBLIC_HEADER include/pkg_HelloJNI.h)
message($ENV{JAVA_HOME}/include)
message($ENV{JAVA_HOME}/include/linux)
target_include_directories(native PRIVATE $ENV{JAVA_HOME}/include $ENV{JAVA_HOME}/include/linux)

set_target_properties(native PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/library)