cmake_minimum_required(VERSION 3.0.0)
project(YadroTestTask VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(target_name file_tape_test)
set(source_list
    file-tape-test.cpp
    ${CMAKE_SOURCE_DIR}/src/tape/file-tape.hpp
    ${CMAKE_SOURCE_DIR}/src/tape/file-tape.cpp
    ${CMAKE_SOURCE_DIR}/src/tape/tape-base.hpp
    ${CMAKE_SOURCE_DIR}/src/utils/config.hpp
    ${CMAKE_SOURCE_DIR}/src/utils/config.cpp
)

add_executable(${target_name} ${source_list})

target_link_libraries(${target_name}
    PRIVATE
        GTest::gtest
        spdlog::spdlog 
        nlohmann_json::nlohmann_json
)

target_include_directories(${target_name}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src/tape
        ${CMAKE_SOURCE_DIR}/src/utils
)



set(target_name tape_sorter_test)
set(source_list
    tape-sorter-test.cpp
    ${CMAKE_SOURCE_DIR}/src/tape-sorter.hpp
    ${CMAKE_SOURCE_DIR}/src/tape-sorter.cpp
    ${CMAKE_SOURCE_DIR}/src/tape/file-tape.hpp
    ${CMAKE_SOURCE_DIR}/src/tape/file-tape.cpp
    ${CMAKE_SOURCE_DIR}/src/tape/tape-base.hpp
    ${CMAKE_SOURCE_DIR}/src/utils/config.hpp
    ${CMAKE_SOURCE_DIR}/src/utils/config.cpp
)

add_executable(${target_name} ${source_list})

target_link_libraries(${target_name}
    PRIVATE
        GTest::gtest
        spdlog::spdlog 
        nlohmann_json::nlohmann_json
)

target_include_directories(${target_name}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src/tape
        ${CMAKE_SOURCE_DIR}/src/utils
        ${CMAKE_SOURCE_DIR}/src
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_configs/config.json ${CMAKE_BINARY_DIR}/tests/config.json COPYONLY)