cmake_minimum_required(VERSION 3.0.0)
project(YadroTestTask VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(target_name ${PROJECT_NAME})
set(source_list
    main.cpp
    tape-sorter.hpp
    tape-sorter.cpp
    utils/cmd-parser.hpp
    utils/cmd-parser.cpp
    utils/config.hpp
    utils/config.cpp
    tape/tape-base.hpp
    tape/file-tape.hpp
    tape/file-tape.cpp
)

add_executable(${target_name} ${source_list})

target_link_libraries(${target_name}
    PRIVATE
        spdlog::spdlog 
        nlohmann_json::nlohmann_json
)

target_include_directories(${target_name}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        utils
        tape
)

configure_file(${CMAKE_SOURCE_DIR}/configs/config.json ${CMAKE_BINARY_DIR}/src/config.json COPYONLY)