# Add all tests to executables.
add_executable(Rpi_Spi_unittest Rpi_Spi_unittest.c)

# Compile features.
#target_compile_features(Rpi_Spi_unittest PRIVATE <...>)

# Link libraries.
target_link_libraries(Rpi_Spi_unittest PRIVATE Rpi_Spi)

# Add test(s).
add_test(NAME Test_Rpi_Spi_unittest COMMAND Rpi_Spi_unittest)
