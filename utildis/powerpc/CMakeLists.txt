cmake_minimum_required(VERSION 3.0)

project(powerpc)

set(SRCS
    chiara-ppc.c
    )
    
set(HEADERS
    ppc.h
    )
add_compile_options(-std=gnu99)    

add_library(powerpc ${SRCS} ${HEADERS})
