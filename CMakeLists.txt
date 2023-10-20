cmake_minimum_required(VERSION 3.12)

project(bayan)

set(CMAKE_CXX_STANDARD 17)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK OFF)

find_package(Boost 1.65.1 REQUIRED COMPONENTS program_options filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})

	add_executable(bayan
        src/main.cpp
        src/differ.cpp
        src/utils.cpp
    )

    target_link_libraries(bayan ${Boost_LIBRARIES})
endif()

target_include_directories(bayan
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS bayan RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME "bayan")
set(CPACK_PACKAGE_CONTACT art.shestakov@icloud.com)
include(CPack)
