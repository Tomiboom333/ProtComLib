#ifndef I2C_H
#define I2C_H
#include "stm32f103xb.h"

void i2c_init(I2C_TypeDef* I2Cx);
void i2c_start(I2C_TypeDef* I2Cx);
void i2c_stop(I2C_TypeDef* I2Cx);
void i2c_send_direccion(I2C_TypeDef* I2Cx, char direccion);
void i2c_send_byte(I2C_TypeDef* I2Cx, char dato);
char i2c_recibir_byte_ack(I2C_TypeDef* I2Cx);
char i2c_recibir_byte_nack(I2C_TypeDef* I2Cx);

#endif
