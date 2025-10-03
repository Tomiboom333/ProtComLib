#include "i2c.h"
#include "stm32f103xb.h"
#define SCL1 6
#define SDA1 7
#define SCL2 10
#define SDA2 11
void i2c_init(I2C_TypeDef* I2Cx){

    I2Cx -> CR1 |= I2C_CR1_SWRST;
    //trise 
    
    if(I2Cx == I2C1){
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        // Configura SCL1 (AF open-drain)
        GPIOB->CRL &= ~(0xF << SCL1*4);
        GPIOB->CRL |= (0b1110 << SCL1*4);
        // Configura SDA1 (AF open-drain)
        GPIOB->CRL &= ~(0xF << SDA1*4);
        GPIOB->CRL |= (0b1110 << SDA1*4);
        I2Cx -> TRISE 
        I2Cx->CR2 = 36;
    }else if(I2Cx == I2C2){
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        // Configura SCL1 (AF open-drain)
        GPIOB->CRH &= ~(0xF << (SCL2%8)*4);
        GPIOB->CRH |= (0b1110 << (SCL2%8)*4);
        // Configura SDA1 (AF open-drain)
        GPIOB->CRH &= ~(0xF << (SDA2%8)*4);
        GPIOB->CRH |= (0b1110 << (SDA2%8)*4);

        I2Cx->CR2 = 36;
    }
}

void i2c_start(I2C_TypeDef* I2Cx){
    while(!(I2Cx->SR1 & I2C_SR1_SB));
    I2Cx->CR1 |= I2C_CR1_START;
}

void i2c_stop(I2C_TypeDef* I2Cx){
    while(!(I2Cx->SR1 & I2C_SR1_STOPF));
    I2Cx->CR1 |= I2C_CR1_STOP;
}

void i2c_send_direccion(I2C_TypeDef* I2Cx, char direccion){
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));
    I2Cx->DR = direccion;
}

void i2c_send_byte(I2C_TypeDef* I2Cx, char dato){
    while(!(I2Cx->SR1 & I2C_SR1_TXE));
    I2Cx->DR = dato;
}

char i2c_recibir_byte_ack(I2C_TypeDef* I2Cx){
    while(!(I2Cx->SR1 & I2C_SR1_RXNE));
    I2Cx->CR1 |= I2C_CR1_ACK;
    return I2Cx->DR;
}

char i2c_recibir_byte_nack(I2C_TypeDef* I2Cx){
    while(!(I2Cx->SR1 & I2C_SR1_RXNE));
    I2Cx->CR1 &= ~I2C_CR1_ACK;
    return I2Cx->DR;
}
