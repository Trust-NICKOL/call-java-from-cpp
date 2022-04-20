cmake_minimum_required(VERSION 3.5)

project(java_native_interface)
add_executable(java_native_interface_cmake main.cpp)

find_package(JNI)

include_directories(${JNI_INCLUDE_DIRS})
target_link_libraries(java_native_interface_cmake ${JAVA_JVM_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
