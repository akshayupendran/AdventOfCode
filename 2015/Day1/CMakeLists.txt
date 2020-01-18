cmake_minimum_required(VERSION 3.0.0)
project(2015_Day1 VERSION 0.1.0)

include_directories(include)
include_directories(cfg)

file(GLOB SOURCES "src/*.c")

add_executable(2015_Day1 ${SOURCES})
