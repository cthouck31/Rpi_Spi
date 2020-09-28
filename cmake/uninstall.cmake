set(MANIFEST "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt")

message(STATUS "Uninstalling ${PACKAGE_NAME}")

if(NOT EXISTS ${MANIFEST})
    message(FATAL_ERROR "Cannot find install manifest: '${MANIFEST}'")
endif()

# Remove all files.
file(STRINGS ${MANIFEST} files)
foreach(file ${files})
    if(EXISTS ${file})
        message(STATUS "Removing file: '${file}'")

        exec_program(
            ${CMAKE_COMMAND} ARGS "-E remove ${file}"
            OUTPUT_VARIABLE stdout
            RETURN_VALUE result
        )

        if(NOT "${result}" STREQUAL 0)
            message(FATAL_ERROR "Failed to remove '${file}'. Must run as 'sudo'.")
        endif()
    else()
        message(STATUS "File '${file}' does not exist.")
    endif()
endforeach(file)

# Remove all project directories.
exec_program(
    cat ARGS "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt" | xargs -L1 dirname | sudo xargs rmdir -p
    OUTPUT_VARIABLE stdout
    RETURN_VALUE result
)
