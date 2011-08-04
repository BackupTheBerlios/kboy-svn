project(kboy)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 4.7 REQUIRED)

# Other Qt modules than QtCore and QtGui (which are added added as standard) must be enabled before
# include(${QT_USE_FILE}) like this: set (QT_USE_QTXML 1)

# This defines some QT specific cmake macros, defines some variables (like QT_LIBRARIES) according to the formerly set config variables
# and adds the Qt4 include directories
include( ${QT_USE_FILE} )


file(GLOB_RECURSE KBOY_HDR "${CMAKE_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE KBOY_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE KBOY_RES "${CMAKE_SOURCE_DIR}/res/*.qrc")
file(GLOB KBOY_TS "${CMAKE_SOURCE_DIR}/translations/*.ts")
#message("Ressource files: " ${KBOY_TS})

# Add resource files...
qt4_add_resources( KBOY_RC_SRCS ${KBOY_RES} )

# Calling moc...
qt4_wrap_cpp( KBOY_MOC_SRCS ${KBOY_HDR} OPTIONS "-nw" )

# The moc generated files ended up in the build dir, so append it to the include dirs...
include_directories(AFTER src ${CMAKE_BINARY_DIR} )


# TODO:
# Generate extra target to update ts files (from all  sources)
# -_> in general, this target must simply call lupdate ^^
#QT4_CREATE_TRANSLATION (KBOY_QM "${CMAKE_SOURCE_DIR}/src" "kboy_de.ts" "kboy_en.ts")

# This will create qm files for all ts files (one ts file for each translation) using lrelease. This should be done for each build because
# the translated ressources are included into the binary.
QT4_ADD_TRANSLATION(KBOY_QM ${KBOY_TS})

# Add a make target for "kboy" executable which depends on all normal and moc generated source files as well as the translation binaries.
add_executable(kboy ${KBOY_SRC} ${KBOY_RC_SRCS} ${KBOY_MOC_SRCS} ${KBOY_QM})

# let the new target link to Qt4
target_link_libraries(kboy ${QT_LIBRARIES})
