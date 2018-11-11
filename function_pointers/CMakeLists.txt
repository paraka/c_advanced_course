cmake_minimum_required(VERSION 2.8)

project(function_pointers)
 
include_directories(include)
  
file(GLOB SOURCES "src/*.c")
    
add_executable(function_pointers ${SOURCES})
