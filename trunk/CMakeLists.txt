project(kboy)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 4.7 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE KBOY_SRC src/ *.cpp)
qt4_automoc(${KBOY_SRC})
add_executable(kboy ${KBOY_SRC})
include_directories(AFTER src)
target_link_libraries(kboy ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
