cmake_minimum_required(VERSION 3.16)

project(AmeHTTPServer
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(ame_http_server
    src/main_server.cpp
    src/Ame_http_tcpServer.cpp
)

target_include_directories(ame_http_server
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ame_http_server
    PRIVATE
        cxx_std_17
)

