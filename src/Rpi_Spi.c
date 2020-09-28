#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <string.h>

#include "Rpi_Spi/Rpi_Spi.h"

/**
 * Rpi_Spi_open
 * -------------------------------------------
 * @brief Open a Raspberry Pi SPI interface.
 *
 * @param[in] rspi  Raspberry Pi SPI class.
 * @param[in] port  SPI port name (e.g. '/dev/spidev0.0').
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_open(
    Rpi_Spi *rspi,
    const char *port)
{
    int32_t status      = 0;
    uint32_t spiMode    = SPI_MODE_0;
    uint32_t spiWordLen = 8;
    uint32_t spiSpeed   = 10000000; // 10 MHz.
    if (rspi == NULL || port == NULL)
    {
        return -1;
    }

    // Open the port.
    rspi->fd = open(port, O_RDWR);
    if (rspi->fd < 0)
    {
        return rspi->fd;
    }
    strncpy(&rspi->port[0], port, sizeof(rspi->port));

    // Set defaults.
    status = Rpi_Spi_setMode(
                rspi,
                spiMode);
    if (status != 0)
    {
        goto failure;
    }
    status = Rpi_Spi_setWordLen(
                rspi,
                spiWordLen);
    if (status != 0)
    {
        goto failure;
    }
    status = Rpi_Spi_setSpeed(
                rspi,
                spiSpeed);
    if (status != 0)
    {
        goto failure;
    }

    return status;

failure:
    Rpi_Spi_close(rspi);
    return status;
};


/**
 * Rpi_Spi_close
 * -------------------------------------------
 * @brief Close a Raspberry Pi SPI interface.
 *
 * @param[in] rspi  Raspberry Pi SPI class.
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_close(
    Rpi_Spi *rspi)
{
    int32_t status = 0;
    if (rspi->fd >= 0)
    {
        status = close(rspi->fd);
    }

    return status;
};


/**
 * Rpi_Spi_setMode
 * -------------------------------------------
 * @brief Set the SPI mode.
 *
 * @param[in] rspi  Raspberry Pi SPI class.
 * @param[in] mode  SPI mode.
 *                      SPI_MODE_0: CPOL=0, CPHA=0
 *                      SPI_MODE_1: CPOL=0, CPHA=1
 *                      SPI_MODE_2: CPOL=1, CPHA=0
 *                      SPI_MODE_3: CPOL=1, CPHA=1
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_setMode(
    Rpi_Spi *rspi,
    const uint32_t mode)
{
    int32_t status = 0;
    uint32_t spiMode = mode;
    if (rspi == NULL)
    {
        return -1;
    }
    if (rspi->fd < 0)
    {
        return -2;
    }

    // Set SPI mode.
    status = ioctl(rspi->fd, SPI_IOC_WR_MODE, &spiMode);
    if (status < 0)
    {
        return status;
    }
    status = ioctl(rspi->fd, SPI_IOC_RD_MODE, &spiMode);
    if (status < 0)
    {
        return status;
    }

    status = 0;

    rspi->mode = mode;

    return status;
};


/**
 * Rpi_Spi_getMode
 * -------------------------------------------
 * @brief Get the SPI mode.
 *
 * @param[in]  rspi  Raspberry Pi SPI class.
 * @param[out] mode  SPI mode.
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_getMode(
    Rpi_Spi *rspi,
    uint32_t *mode)
{
    if (rspi == NULL)
    {
        return -1;
    }
    if (rspi->fd < 0)
    {
        return -2;
    }

    *mode = rspi->mode;

    return 0;
};


/**
 * Rpi_Spi_setSpeed
 * -------------------------------------------
 * @brief Set the SPI speed.
 *
 * @param[in] rspi  Raspberry Pi SPI class.
 * @param[in] speed SPI speed (in Hz).
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_setSpeed(
    Rpi_Spi *rspi,
    const uint32_t speed)
{
    int32_t status = 0;
    uint32_t spiSpeed = speed;
    if (rspi == NULL)
    {
        return -1;
    }
    if (rspi->fd < 0)
    {
        return -2;
    }

    // Set SPI speed settings.
    status = ioctl(rspi->fd, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed);
    if (status < 0)
    {
        return status;
    }
    status = ioctl(rspi->fd, SPI_IOC_RD_MAX_SPEED_HZ, &spiSpeed);
    if (status < 0)
    {
        return status;
    }

    status = 0;

    rspi->speed = speed;

    return status;
};


/**
 * Rpi_Spi_getSpeed
 * -------------------------------------------
 * @brief Get the SPI speed.
 *
 * @param[in]  rspi  Raspberry Pi SPI class.
 * @param[out] speed SPI speed (in Hz).
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_getSpeed(
    Rpi_Spi *rspi,
    uint32_t *speed)
{
    int32_t status = 0;
    if (rspi == NULL)
    {
        return -1;
    }
    if (rspi->fd < 0)
    {
        return -2;
    }

    *speed = rspi->speed;

    return 0;
};


/**
 * Rpi_Spi_setWordLen
 * -------------------------------------------
 * @brief Set the SPI word length.
 *
 * @param[in] rspi  Raspberry Pi SPI class.
 * @param[in] len   Word length (in bits).
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_setWordLen(
    Rpi_Spi *rspi,
    const uint32_t len)
{
    int32_t status = 0;
    uint32_t spiWordLen = len;
    if (rspi == NULL)
    {
        return -1;
    }
    if (rspi->fd < 0)
    {
        return -2;
    }
    if (len < 1)
    {
        return -3;
    }

    // Set SPI word settings.
    status = ioctl(rspi->fd, SPI_IOC_WR_BITS_PER_WORD, &spiWordLen);
    if (status < 0)
    {
        return status;
    }
    status = ioctl(rspi->fd, SPI_IOC_RD_BITS_PER_WORD, &spiWordLen);
    if (status < 0)
    {
        return status;
    }

    status = 0;

    rspi->wordLen = len;

    return status;
};


/**
 * Rpi_Spi_getWordLen
 * -------------------------------------------
 * @brief Get the SPI word length.
 *
 * @param[in]  rspi  Raspberry Pi SPI class.
 * @param[out] len   Word length (in bits).
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_getWordLen(
    Rpi_Spi *rspi,
    uint32_t *len)
{
    int32_t status = 0;
    if (rspi == NULL)
    {
        return -1;
    }
    if (rspi->fd < 0)
    {
        return -2;
    }

    *len = rspi->wordLen;

    return 0;
};


/**
 * Rpi_Spi_transfer
 * -------------------------------------------
 * @brief Perform a SPI transaction.
 *
 * @param[in]  rspi Raspberry Pi SPI class.
 * @param[out] out  SPI receive data.
 * @param[in]  in   SPI transmit data.
 * @param[in]  len  Number of bytes to transfer.
 *
 * @returns 0 on success, error otherwise.
*/
int32_t
Rpi_Spi_transfer(
    Rpi_Spi *rspi,
    uint8_t *out,
    uint8_t *in,
    const uint32_t len)
{
    int32_t status = 0;
    struct spi_ioc_transfer xfer;
    if (rspi == NULL)
    {
        return -1;
    }
    if (out == NULL || in == NULL)
    {
        return -2;
    }

    // Setup transfer.
    xfer.tx_buf      = (uint64_t)in;
    xfer.rx_buf      = (uint64_t)out;
    xfer.len         = len;
    xfer.delay_usecs = 0;
    xfer.speed_hz    = rspi->speed;
    xfer.bits_per_word = rspi->wordLen;
    xfer.cs_change   = 0;

    // Perform transfer.
    status = ioctl(
                rspi->fd,
                SPI_IOC_MESSAGE(1),
                &xfer);

    return status;
};
