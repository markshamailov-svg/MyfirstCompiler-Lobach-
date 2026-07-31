cmake_minimum_required(VERSION 3.10)

project(LobachCompiler C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(
        lobach
        main.c
        lexer.c
        parcer.c
        generateC.c
)