#include "spi.h"
#define SCK1 5
#define MISO1 6
#define MOSI1 7
#define SCK2 13
#define MISO2 14
#define MOSI2 15
void spi_init(SPI_TypeDef* SPIx){
    if(SPIx == SPI1){
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

        // Configura SCK1 (AF push-pull)
        GPIOA->CRL &= ~(0xF << SCK1*4);
        GPIOA->CRL |= (0b1011 << SCK1*4);

        // Configura MISO1 (input floating)
        GPIOA->CRL &= ~(0xF << MISO1*4);
        GPIOA->CRL |= (0b0100 << MISO1*4);

        // Configura MOSI1 (AF push-pull)
        GPIOA->CRL &= ~(0xF << MOSI1*4);
        GPIOA->CRL |= (0b1011 << MOSI1*4);

        SPIx->CR1 |= SPI_CR1_MSTR; //master
        SPIx->CR1 |= SPI_CR1_SSM; //software slave management
        SPIx->CR1 |= SPI_CR1_SSI; //internal slave select
        SPIx->CR1 |= SPI_CR1_BR_0; //fPCLK/4
        SPIx->CR1 |= SPI_CR1_CPOL; //clock polarity high
        SPIx->CR1 |= SPI_CR1_CPHA; //clock phase second edge
        SPIx->CR1 |= SPI_CR1_SPE; //enable

    }else if(SPIx == SPI2){
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

        // Configura SCK2 (AF push-pull)
        GPIOB->CRH &= ~(0xF << (SCK2%8)*4);
        GPIOB->CRH |= (0b1011 << (SCK2%8)*4);

        // Configura MISO2 (input floating)
        GPIOB->CRH &= ~(0xF << (MISO2%8)*4);
        GPIOB->CRH |= (0b0100 << (MISO2%8)*4);

        // Configura MOSI2 (AF push-pull)
        GPIOB->CRH &= ~(0xF << (MOSI2%8)*4);
        GPIOB->CRH |= (0b0100 << (MOSI2%8)*4);
    }   
}