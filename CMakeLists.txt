cmake_minimum_required(VERSION 3.30)
project(FileMan C)

set(CMAKE_C_STANDARD 11)

add_executable(FileMan main.c
        text_file_man.c
        text_file_man.h
        dat_file_man.c
        dat_file_man.h)
