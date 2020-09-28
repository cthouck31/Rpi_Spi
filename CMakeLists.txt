################################################################################
# Set up library.
cmake_minimum_required(VERSION 3.13)

project(
    Rpi_Spi
    VERSION 1.0.0
    DESCRIPTION "Base for stand-alone communications library."
)

# Testing.
enable_testing()

################################################################################
# Options.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCOMMS_ENDIAN=1")

################################################################################
# Find packages.

# Add modules path.
set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules"
)

# Look for Doxygen.
find_package(Doxygen)
if (Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found. Skipping documentation...")
endif()

################################################################################
# Add all buildable sub-directories.

# Source code.
add_subdirectory(src)
# Application(s).
add_subdirectory(apps)
# Tests.
add_subdirectory(tests)

################################################################################
# Install.
include(GNUInstallDirs)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)
install(
    DIRECTORY
    include/
    DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}
)

# Create configuration file.
install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Config"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
export(
    TARGETS
    ${PROJECT_NAME}
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)
install(
    EXPORT
    "${PROJECT_NAME}Config"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake"
)

#message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake")

# Uninstall.
add_custom_target(
    uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake"
)
