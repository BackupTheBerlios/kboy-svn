project(kboy)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(kboy_SRCS kboy.cpp main.cpp)
qt4_automoc(${kboy_SRCS})
add_executable(kboy ${kboy_SRCS})
target_link_libraries(kboy ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
