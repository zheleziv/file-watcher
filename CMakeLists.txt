cmake_minimum_required(VERSION 3.15)
project(
        FileWatcher
        LANGUAGES CXX
        VERSION 1.0.0
)

add_subdirectory(libs)

set(
        HEADER_FILES
        src/Configurator.h
        src/Task.h
        src/InotifyChecker.h
        src/LocalDirBackuper.h
)

set(
        SOURCE_FILES
        src/Configurator.cpp
        src/Task.cpp
        src/InotifyChecker.cpp
        src/LocalDirBackuper.cpp
        main.cpp
)

add_executable(FileWatcher ${HEADER_FILES} ${SOURCE_FILES})

find_package(Boost REQUIRED COMPONENTS program_options filesystem)
target_link_libraries(
        FileWatcher
        PUBLIC
        Boost::program_options
        Boost::filesystem
        Checker
        Backuper
        Process
        pthread
)