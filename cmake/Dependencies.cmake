include(ExternalProject)
set(Boost_URL "https://sourceforge.net/projects/boost/files/boost/1.62.0/boost_1_62_0.tar.bz2")
set(Boost_SHA1 "5fd97433c3f859d8cbab1eaed4156d3068ae3648")
set(Boost_INSTALL ${CMAKE_BINARY_DIR}/third_party/Boost)

ExternalProject_Add(Boost
        INSTALL_DIR ${Boost_INSTALL}
        URL ${Boost_URL}
        URL_HASH SHA1=${Boost_SHA1}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND
        ${Boost_INSTALL}/src/Boost/bootstrap.sh
        --with-libraries=system
        --with-libraries=thread
        --with-libraries=chrono
        --with-libraries=filesystem
        --with-libraries=program_options
        --prefix=${Boost_INSTALL}
        BUILD_COMMAND
        ${Boost_INSTALL}/src/Boost/b2 install link=static variant=release threading=multi  cxxflags=-fPIC cflags=-fPIC
        INSTALL_COMMAND
        ${Boost_INSTALL}/src/Boost/bjam cxxflags=-fPIC cflags=-fPIC link=static
)

EXTERNALPROJECT_GET_PROPERTY(Boost install_dir)

if (EXISTS ${install_dir}/include AND EXISTS ${install_dir}/lib)
    set(Boost_INCLUDE_DIR ${install_dir}/include)
    set(BOOST_LIB_DIR ${install_dir}/lib)

    set(Boost_System ${BOOST_LIB_DIR}/libboost_system.a)
    set(Boost_Thread ${BOOST_LIB_DIR}/libboost_thread.a)
    set(Boost_Chrono ${BOOST_LIB_DIR}/libboost_chrono.a)
    set(Boost_Filesystem ${BOOST_LIB_DIR}/libboost_filesystem.a)
    set(Boost_Program_Options ${BOOST_LIB_DIR}/libboost_program_options.a)

    add_library(boost_header INTERFACE)
    add_library(Boost::Boost ALIAS boost_header)
    target_include_directories(boost_header INTERFACE ${Boost_INCLUDE_DIR})

    add_library(boost_system INTERFACE)
    add_library(Boost::system ALIAS boost_system)
    target_include_directories(boost_system INTERFACE ${Boost_INCLUDE_DIR})
    target_link_libraries(boost_system
            INTERFACE
            ${Boost_System}
    )

    add_library(boost_program_options INTERFACE)
    add_library(Boost::program_options ALIAS boost_program_options)
    target_include_directories(boost_program_options INTERFACE ${Boost_INCLUDE_DIR})
    target_link_libraries(boost_program_options
            INTERFACE
            ${Boost_Program_Options}
    )
else ()
    message(WARNING "Не заданы переменные для поиска boost Boost_INCLUDE_DIR и BOOST_LIB_DIR")
endif ()

