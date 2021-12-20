cmake_minimum_required(VERSION 3.0.0)

#Nome no projeto
project(trabalho)

set(CMAKE_CXX_STANDARD 11)

#pastas de arquivos src
file(GLOB SOURCES

    sources/*.cpp
    
)

add_executable(trabalho ${SOURCES})

#pasta dos arquivos headers
target_include_directories(trabalho PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} / headers)
