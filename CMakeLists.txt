cmake_minimum_required(VERSION 3.15)
project(
        FileWatcher
        LANGUAGES CXX
        VERSION 1.0.0
)

include(cmake/Dependencies.cmake)

set(
        HEADER_FILES

)

set(
        SOURCE_FILES
        src/main.cpp

)

add_executable(FileWatcher ${HEADER_FILES} ${SOURCE_FILES})

find_package(Boost)
if (NOT ${Boost_FOUND})
    message(WARNING "Необходимо установить Boost (--target Boost или через пакетный менеджер, после чего перезапустить cmake)")
elseif ()
    target_link_libraries(FileWatcher PUBLIC Boost::Boost Boost::program_options)
endif ()