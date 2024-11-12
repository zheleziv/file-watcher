project(
        Process
        LANGUAGES CXX
        VERSION 1.0.0
)

set(
        HEADER_FILES
        include/Process/Interface.h
        include/Process/Manager.h
)

set(
        SOURCE_FILES
        src/Manager.cpp
)

add_library(Process STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(Process PUBLIC include)