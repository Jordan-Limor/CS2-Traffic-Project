cmake_minimum_required(VERSION 3.20)
project(traffic_group C)

set(CMAKE_C_STANDARD 99)

add_executable(traffic_group main.c streets.c cars.c)
