#ifndef SPI_H
#define SPI_H
#include "stm32f103xb.h"

void spi_init(SPI_TypeDef*);
void spi_ss(SPI_TypeDef*); //slave select
void spi_ds(SPI_TypeDef*); //deseleccionar slave
char spi_rw_byte(SPI_TypeDef*, char); // read/write

#endif