cmake_minimum_required(VERSION 3.0)

project(thechiara)

add_subdirectory(utildis/powerpc)

set(SRCS
    main.c
    )
    add_compile_options(-std=gnu99)    
add_executable(thechiara ${SRCS})

target_link_libraries(thechiara powerpc)
