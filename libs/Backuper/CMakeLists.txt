project(
        Backuper
        LANGUAGES CXX
        VERSION 1.0.0
)

set(
        HEADER_FILES
        include/Backuper/Interface.h
)

add_library(Backuper INTERFACE ${HEADER_FILES} )
target_include_directories(Backuper INTERFACE include)