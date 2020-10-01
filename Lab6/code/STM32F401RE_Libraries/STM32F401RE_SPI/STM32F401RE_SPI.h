// STM32F401RE_SPI.h
// Header for SPI functions

#ifndef STM32F4_SPI_H
#define STM32F4_SPI_H

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define SPI1_BASE (0x40013000UL)
#define __IO volatile

///////////////////////////////////////////////////////////////////////////////
// Bitfield structs
///////////////////////////////////////////////////////////////////////////////

typedef struct {
  __IO uint32_t CPHA        : 1;
  __IO uint32_t CPOL        : 1;
  __IO uint32_t MSTR        : 1;
  __IO uint32_t BR          : 3;
  __IO uint32_t SPE         : 1;
  __IO uint32_t LSBFIRST    : 1;
  __IO uint32_t SSI         : 1;
  __IO uint32_t SSM         : 1;
  __IO uint32_t RXONLY      : 1;
  __IO uint32_t DFF         : 1;
  __IO uint32_t CRCNEXT     : 1;
  __IO uint32_t CRCEN       : 1;
  __IO uint32_t BIDIOE      : 1;
  __IO uint32_t BIDIMODE    : 1;
  __IO uint32_t             : 16;
} SPI_CR1_bits;

typedef struct {
  __IO uint32_t RXDMAEN     : 1;
  __IO uint32_t TXDMAEN     : 1;
  __IO uint32_t SSOE        : 1;
  __IO uint32_t             : 1;
  __IO uint32_t FRF         : 1;
  __IO uint32_t ERRIE       : 1;
  __IO uint32_t RXNEIE      : 1;
  __IO uint32_t TXEIE       : 1;
  __IO uint32_t             : 24;
} SPI_CR2_bits;

typedef struct {
  __IO uint32_t RXNE        : 1;
  __IO uint32_t TXE         : 1;
  __IO uint32_t CHSIDE      : 1;
  __IO uint32_t UDR         : 1;
  __IO uint32_t CRCERR      : 1;
  __IO uint32_t MODF        : 1;
  __IO uint32_t OVR         : 1;
  __IO uint32_t BSY         : 1;
  __IO uint32_t FRE         : 1;
  __IO uint32_t DFF         : 1;
  __IO uint32_t CRCNEXT     : 1;
  __IO uint32_t CRCEN       : 1;
  __IO uint32_t BIDIOE      : 1;
  __IO uint32_t BIDIMODE    : 1;
  __IO uint32_t             : 16;
} SPI_SR_bits;

typedef struct {
  __IO uint32_t DR  : 16;
  __IO uint32_t     : 16;
} SPI_DR_bits;


typedef struct {
  __IO SPI_CR1_bits CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
  __IO SPI_CR2_bits CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
  __IO SPI_SR_bits SR;         /*!< SPI status register,                                Address offset: 0x08 */
  __IO SPI_DR_bits DR;         /*!< SPI data register,                                  Address offset: 0x0C */
  __IO uint32_t CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
  __IO uint32_t RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
  __IO uint32_t TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
  __IO uint32_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
  __IO uint32_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
} SPI_TypeDef;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define SPI1 ((SPI_TypeDef *) SPI1_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

/* Enables the SPI peripheral and intializes its clock speed (baud rate), polarity, and phase.
 *    -- clkdivide: (0x01 to 0xFF). The SPI clk will be the master clock / clkdivide.
 *    -- cpol: clock polarity (0: inactive state is logical 0, 1: inactive state is logical 1).
 *    -- cpha: clock phase (1: data changed on leading edge of clk and captured on next edge, 
 *          0: data captured on leading edge of clk and changed on next edge)
 * Note: the SPI mode register is set with the following unadjustable settings:
 *    -- Master mode
 *    -- Fixed peripheral select
 *    -- Chip select lines directly connected to peripheral device
 *    -- Mode fault detection enabled
 *    -- WDRBT disabled
 *    -- LLB disabled
 *    -- PCS = 0000 (Peripheral 0 selected), means NPCS[3:0] = 1110
 * Refer to the datasheet for more low-level details. */ 
void spiInit(uint32_t clkdivide, uint32_t cpol, uint32_t ncpha);

/* Transmits a character (1 byte) over SPI and returns the received character.
 *    -- send: the character to send over SPI
 *    -- return: the character received over SPI */
uint8_t spiSendReceive(uint8_t send);

/* Transmits a short (2 bytes) over SPI and returns the received short.
 *    -- send: the short to send over SPI
 *    -- return: the short received over SPI */
uint16_t spiSendReceive16(uint16_t send);

#endif