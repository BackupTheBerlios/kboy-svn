project(kboy)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 4.7 REQUIRED)

include( ${QT_USE_FILE} )

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE KBOY_HDR "${CMAKE_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE KBOY_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE KBOY_RES "${CMAKE_SOURCE_DIR}/res/*.qrc")
#message("Files to compile: " ${KBOY_SRC})
#message("Header files to moc: " ${KBOY_HDR})
message("Ressource files: " ${KBOY_RES})

# Add resource files...
qt4_add_resources( KBOY_RC_SRCS ${KBOY_RES} )

# Calling moc...
qt4_wrap_cpp( KBOY_MOC_SRCS ${KBOY_HDR} )

#qt4_automoc(${KBOY_SRC})
add_executable(kboy ${KBOY_SRC} ${KBOY_RC_SRCS} ${KBOY_MOC_SRCS})

# The moc generated files ended up in the build dir, so append it to the include dirs...
include_directories(AFTER src ${CMAKE_BINARY_DIR} )

target_link_libraries(kboy ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
