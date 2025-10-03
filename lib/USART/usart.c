#include "usart.h"

#define TX1 9
#define RX1 10
#define TX2 2
#define RX2 3
#define TX3 10
#define RX3 11

void usart_init(USART_TypeDef* usartx, int baudrate){
    usartx -> CR1 |= USART_CR1_UE; 
    usartx -> CR1 |= USART_CR1_TE;
    usartx -> CR1 |= USART_CR1_RE;
    
    if(usartx == USART1){
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

        // Configura TX1 (AF push-pull)
        GPIOA->CRH &= ~(0xF << (TX1%8)*4);
        GPIOA->CRH |= (0b1011 << (TX1%8)*4);

        // Configura RX1 (input floating)
        GPIOA->CRH &= ~(0xF << (RX1%8)*4);
        GPIOA->CRH |= (0b0100 << (RX1%8)*4);

        usartx -> BRR = (16 * baudrate)/72000000; //clock de 72MHz
    }
    else if(usartx == USART2){
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

        // Configura TX2 (AF push-pull)
        GPIOA->CRL &= ~(0xF << TX2*4);
        GPIOA->CRL |= (0b1011 << TX2*4);

        // Configura RX2 (input floating)
        GPIOA->CRL &= ~(0xF << RX2*4);
        GPIOA->CRL |= (0b0100 << RX2*4);

        usartx -> BRR = (16 * baudrate)/36000000; //clock de 36MHz
    }
    else if(usartx == USART3){
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

        // Configura TX3 (AF push-pull)
        GPIOA->CRH &= ~(0xF << (TX3%8)*4);
        GPIOA->CRH |= (0b1011 << (TX3%8)*4);

        // Configura RX3 (input floating)
        GPIOA->CRH &= ~(0xF << (RX3%8)*4);
        GPIOA->CRH |= (0b0100 << (RX3%8)*4);

        usartx -> BRR = (16 * baudrate)/36000000; //clock de 36MHz
    }
}
void usart_send_char(USART_TypeDef* usartx, char letra){
    while(!(usartx->SR & USART_SR_TXE)); 
    usartx->DR = letra;
}

void usart_send_string(USART_TypeDef* usartx, char* palabra){
    while(*palabra){
        usart_send_char(usartx, *palabra++);
    }
}

char usart_recibir_char(USART_TypeDef* usartx){
    while(!(usartx->SR & USART_SR_RXNE));
    return usartx->DR;
}