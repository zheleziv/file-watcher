project(
        Checker
        LANGUAGES CXX
        VERSION 1.0.0
)

set(
        HEADER_FILES
        include/Checker/Interface.h
)

add_library(Checker INTERFACE )
target_include_directories(Checker INTERFACE include)