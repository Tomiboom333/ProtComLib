#include "spi.h"
#define SS1 4
#define SCK1 5
#define MISO1 6
#define MOSI1 7
#define SS2 12
#define SCK2 13
#define MISO2 14
#define MOSI2 15

void spi_init(SPI_TypeDef* SPIx){

    SPIx->CR1 |= SPI_CR1_MSTR;
    SPIx->CR1 |= SPI_CR1_SSM; 
    SPIx->CR1 |= SPI_CR1_SSI; 
    SPIx->CR1 |= SPI_CR1_BR_0;
    SPIx->CR1 &= ~SPI_CR1_CPOL;
    SPIx->CR1 &= ~SPI_CR1_CPHA;
    SPIx->CR1 |= SPI_CR1_SPE; 

    if(SPIx == SPI1){
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
        // Configura SS1 (output push-pull)
        GPIOA->CRL &= ~(0xF << SS1*4);
        GPIOA->CRL |= (0b0011 << SS1*4);

        // Configura SCK1 (AF push-pull)
        GPIOA->CRL &= ~(0xF << SCK1*4);
        GPIOA->CRL |= (0b1011 << SCK1*4);

        // Configura MISO1 (input floating)
        GPIOA->CRL &= ~(0xF << MISO1*4);
        GPIOA->CRL |= (0b0100 << MISO1*4);

        // Configura MOSI1 (AF push-pull)
        GPIOA->CRL &= ~(0xF << MOSI1*4);
        GPIOA->CRL |= (0b1011 << MOSI1*4);

    }else if(SPIx == SPI2){
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

        // Configura SS2 (output push-pull)
        GPIOB->CRH &= ~(0xF << (SS2%8)*4);
        GPIOB->CRH |= (0b0011 << (SS2%8)*4);

        // Configura SCK2 (AF push-pull)
        GPIOB->CRH &= ~(0xF << (SCK2%8)*4);
        GPIOB->CRH |= (0b1011 << (SCK2%8)*4);

        // Configura MISO2 (input floating)
        GPIOB->CRH &= ~(0xF << (MISO2%8)*4);
        GPIOB->CRH |= (0b0100 << (MISO2%8)*4);

        // Configura MOSI2 (AF push-pull)
        GPIOB->CRH &= ~(0xF << (MOSI2%8)*4);
        GPIOB->CRH |= (0b1011 << (MOSI2%8)*4);
    }   
}
void spi_ss(SPI_TypeDef* SPIx){ 
    if(SPIx == SPI1){
        GPIOA->BSRR |= (1 << SS1); //SS1 en 1
    }else if(SPIx == SPI2){
        GPIOB->BSRR |= (1 << SS2); //SS2 en 1
    }
}
void spi_nss(SPI_TypeDef* SPIx){ 
    if(SPIx == SPI1){
        GPIOA->BRR |= (1 << SS1); //SS1 en 0
    }else if(SPIx == SPI2){
        GPIOB->BRR |= (1 << SS2); //SS2 en 0
    }
}
char spi_rw_byte(SPI_TypeDef* SPIx, char data){
    while(!(SPIx->SR & SPI_SR_TXE)); 
    SPIx->DR = data; //envia dato
    while(!(SPIx->SR & SPI_SR_RXNE)); 
    return SPIx->DR; //lee dato
}