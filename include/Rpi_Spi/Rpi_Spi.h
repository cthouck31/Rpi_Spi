#ifndef RPI_SPI_H
#define RPI_SPI_H

#include <stdint.h>


/**
 * @brief Raspberry Pi SPI class.
 *
 * @note Contains all relevant variables to
 * control the SPI Linux driver (spidev).
 */
typedef struct Rpi_Spi
{
    /** @brief File descriptor. */
    int32_t fd;
    /** @brief Port name. */
    char port[128];
    /** @brief SPI bit rate (Hz). */
    uint32_t speed;
    /** @brief SPI word length (in bits). */
    uint32_t wordLen;
    /** @brief SPI mode. */
    uint32_t mode;

} Rpi_Spi;


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
    const char *port);


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
    Rpi_Spi *rspi);


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
    const uint32_t mode);


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
    uint32_t *mode);


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
    const uint32_t speed);


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
    uint32_t *speed);


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
    const uint32_t len);


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
    uint32_t *len);


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
 * @returns Number of bytes transferred.
*/
int32_t
Rpi_Spi_transfer(
    Rpi_Spi *rspi,
    uint8_t *out,
    uint8_t *in,
    const uint32_t len);


#endif // RPI_SPI_H
