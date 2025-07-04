#pragma once
#include <Arduino.h>

class CONVERT  {
  public: 
  uint16_t H              = 0;                  //Часы
  uint8_t m               = 0;                  //Минуты
  uint8_t s               = 0;                  //Секунды

  //Конвертируем секунды в часы/минуты/секунды 
  void TIME_TO_DATE(uint32_t TIME)
  {
      H = TIME / 3600000;
      m = TIME / 1000 % 3600 / 60;
      s = TIME / 1000 % 3600 % 60;
  }
};
