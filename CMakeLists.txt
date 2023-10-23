cmake_minimum_required(VERSION 3.12)

project(bayan)

find_package(Boost REQUIRED COMPONENTS program_options filesystem)

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
