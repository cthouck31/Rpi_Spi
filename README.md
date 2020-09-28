# Rpi_Spi
Simple Raspberry PI SPI C library using base Linux SPI driver (spidev).

# Description
The __Rpi_Spi__ library is a simple wrapper for the Linux SPI driver (spidev). The library targets the generic Raspberry Pi platform.

The following code outlines the basic usage of the __Rpi_Spi__ library:

```c
// Simple example of the Raspberry Pi SPI library (Rpi_Spi).
#include <Rpi_Spi/Rpi_Spi.h>
#include <stdio.h>

int
main()
{
  int32_t status;
  int32_t nsent;
  uint8_t txBuf[3];
  uint8_t rxBuf[3];
  Rpi_Spi spi;
  
  // Open the SPI interface.
  // Default settings:
  //    Mode:           SPI_MODE_0
  //    Speed:          10000000 (10 MHz)
  //    Bits per Word:  8
  status = Rpi_Spi_open(
            &spi,
            "/dev/spidev0.0");
  if (status != 0)
  {
    printf("%s: Failed to open SPI device @ \'%s\' (status=%d).\n",
           __file__,
           "/dev/spidev0.0",
           status);
    return status;
  }
  
  // Optional: Set SPI settings.
  status = Rpi_Spi_setSpeed(
            &spi,
            5000000);
  if (status != 0)
  {
    printf("%s: Failed to set SPI device speed @ \'%s\' (status=%d).\n",
           __file__,
           "/dev/spidev0.0",
           status);
    goto finished;
  }
  
  
  // Perform a transfer.
  nsent = Rpi_Spi_transfer(
            &spi,
            rxBuf,
            txBuf,
            3);
  if (nsent != 3)
  {
    printf("%s: Failed to perform SPI transfer (nsent=%d).\n",
           __file__,
           nsent);
  }
 
finished:
  status = Rpi_Spi_close(&spi);
  if (status != 0)
  {
    printf("%s: Failed to close SPI device @ \'%s\' (status=%d).\n",
           __file__,
           "/dev/spidev0.0",
           status);
  }
  
  return status;
};
```

# Contributing
Feel free to contribute! The idea of the project is to provide a simple SPI interface; the simpler, the better.
