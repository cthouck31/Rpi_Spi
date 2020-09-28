#include "Rpi_Spi/Rpi_Spi.h"
#include <assert.h>
#include <stdio.h>

int
main()
{
    int32_t status = 0;
    uint8_t out[8];
    uint8_t in[8];
    uint32_t len = 3;
    uint32_t k;
    Rpi_Spi rspi;

    status = Rpi_Spi_open(
                &rspi,
                "/dev/spidev0.0");
    if (status != 0)
    {
        printf("Rpi_Spi: Failed to open port \'%s\' (status=%d).\n",
            "/dev/spidev0.0",
            status);
    }
    assert(status == 0);

    in[0] = 0xaa;
    in[1] = 0xbb;
    in[2] = 0xcc;

    status = Rpi_Spi_transfer(
                &rspi,
                out,
                in,
                len);

    for (k = 0; k < 3; k++)
    {
        printf("in[%u]=%u (==) out[%u]=%u\n",
            k, in[k],
            k, out[k]);
        assert(in[k] == out[k]);
    }

finished:
    Rpi_Spi_close(&rspi);
    return status;
};
