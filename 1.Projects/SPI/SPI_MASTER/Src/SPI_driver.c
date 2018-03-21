#include "../Inc/SPI_driver.h"
#include "../Inc/GPIO_driver.h"


void SPIInit(SPI_TypeDef *SPIx, uint32_t mode, uint32_t baudrate, uint32_t direction, uint32_t cpha, uint32_t cpol, uint32_t size, uint32_t firstBit){
	/* Turn on the clock for the GPIO whose pin to be configured */
	if(SPIx == SPI1)	_SPI1_CLK_ENABLE();
	else if(SPIx == SPI2)	_SPI2_CLK_ENABLE();
	else if(SPIx == SPI3)	_SPI3_CLK_ENABLE();

	
	/* Configure mode: master/slave */
	SPIx->CR1 |= mode;	
	/* Configure baudrate prescaler */
	SPIx->CR1 |= baudrate;
	/* Configure direction */
	SPIx->CR1 |= direction;
	/* Configure clock phase */
	SPIx->CR1 |= cpha;
	/* Configure clock polarity */
	SPIx->CR1 |= cpol;
	/* Configure data size */
	SPIx->CR1 |= size;
	/* Configure first bit mode */
	SPIx->CR1 |= firstBit;
	
	/* Enable SPI */
	SPIx->CR1 |= 1 << 6;
}


uint8_t SPISend(SPI_TypeDef *SPIx, uint8_t data){
	SPIx->DR = data;
	/*
	//Wait until the data has been transmitted.
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE));
	// Wait for any data on MISO pin to be received.
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));
	//All data transmitted/received but SPI may be busy so wait until done.
	while (SPI1->SR & SPI_I2S_FLAG_BSY);
	*/
	return(SPI1->DR);
}
