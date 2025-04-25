cmake_minimum_required(VERSION 3.16)

project(random_text_graph_generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(random_text_graph_generator main.cpp
    RandomGraphText.cpp
    RandomGraphText.h
    input.h
    threadpool.h)

include(GNUInstallDirs)
install(TARGETS random_text_graph_generator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
