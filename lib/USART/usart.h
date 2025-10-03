#ifndef USART_H
#define USART_H
#include "stm32f103xb.h"
void usart_init(USART_TypeDef* usartx, int baudrate);
void usart_send_char(USART_TypeDef* usartx, char letra);
void usart_send_string(USART_TypeDef* usartx, char* palabra);
char usart_recibir_char(USART_TypeDef* usartx);
#endif