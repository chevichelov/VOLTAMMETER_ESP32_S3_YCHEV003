#pragma once
#include <Arduino.h>

class CONFIG  {
  public: 
    uint16_t EEPROM_LIMIT           = 512;    //Размер EEPROM
    uint8_t PIN_ANALOG_READ         = 6;      //Пин для отключения/включения нагрузки 

    uint8_t INA226_CH1              = 0x40;   //I2C адрес INA226 канал 1
    uint8_t INA226_CH2              = 0x44;   //I2C адрес INA226 канал 2
    uint8_t INA226_CH3              = 0x45;   //I2C адрес INA226 канал 3
    
    uint8_t TP_RST                  = 1;      // Touch screen reset pin
    uint8_t LCD_BL                  = 2;      // LCD backlight pinout
    uint8_t LCD_RST                 = 3;      // LCD reset pin
    uint8_t SD_CS                   = 4;      // SD card select pin
    uint8_t USB_SEL                 = 5;      // USB select pin
    
    uint8_t EXAMPLE_I2C_SDA_PIN     = 8;      // I2C data line pins
    uint8_t EXAMPLE_I2C_SCL_PIN     = 9;      // I2C clock line pin
    
    uint8_t SD_MOSI                 = 11;     // SD card master output slave input pin
    uint8_t SD_CLK                  = 12;     // SD card clock pin
    uint8_t SD_MISO                 = 13;     // SD card master input slave output pin
    int8_t  SD_SS                   = -1;     // SD card select pin (not used)
};
