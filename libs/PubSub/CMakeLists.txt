project(
        PubSub
        LANGUAGES CXX
        VERSION 1.0.0
)

set(
        HEADER_FILES
        include/PubSub/Subscriber.h
        include/PubSub/Publisher.h
)

set(
        SOURCE_FILES
        src/Publisher.cpp
)

add_library(PubSub STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(PubSub PUBLIC include)