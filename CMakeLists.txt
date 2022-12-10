cmake_minimum_required(VERSION 3.10)

SET(CMAKE_C_COMPTLER gcc)
SET(CMAKE_CXX_COMPTLER g++)
SET(CMAKE_ASM_COMPTLER gcc)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/)
project(Snake)

add_executable(Snake code/main.c)
