# Add the executable.
add_executable(TestApp TestApp.c)

# Compile features.
#target_compile_features(TestApp PRIVATE <...>)

# Link libraries.
target_link_libraries(TestApp PRIVATE Rpi_Spi)
