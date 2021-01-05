cmake_minimum_required(VERSION 3.17)
project(exercisesC C)

set(CMAKE_C_STANDARD 99)

file(GLOB files *.c)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(${exe} ${file})
    message(\ \ \ \ --\ src/${exe}.c\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()