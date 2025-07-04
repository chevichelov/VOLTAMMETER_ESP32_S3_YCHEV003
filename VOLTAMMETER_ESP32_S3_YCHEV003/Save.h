#pragma once
#include <Arduino.h>

struct __attribute__((__packed__)) SAVE  {
  bool IS_ACTIVE[3]                 = {false, false, false};        //Запись каналов на SD карту
  bool IS_LIMIT                     = false;                        //Ограничитель нагрузки включен/выключен
  float LIMIT[2]                    = {0, 0};                       //Значение лимитов
  uint8_t COUNT_LIMIT_DOWN[2]       = {0, 0};                       //Вспомогательные переменные для лимитов
  uint8_t SELECT_LIMIT              = 0;                            //Вспомогательные переменные для лимитов
  bool IS_SELECT_LIMIT              = false;                        //Вспомогательные переменные для лимитов
  uint8_t ACTIV_NAMBER[3]           = {0, 0, 0};                    //Текущий активный профиль
  float CURRENT_HOUR[3][5]          = {                             //Ампер-час
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}
                                      };                                         
  float WATT_HOUR[3][5]             = {                             //Ватт-час

                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}
                                      };                                             
  uint32_t SET_MILLISECOND[3][5]    = {                             //Время для расчёта емкости


                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}
                                      };                                   
  uint16_t COLOR[5][3]              = {                             //Палитра цветов
                                      {0xffff, 0xf800, 0x07e0},
                                      {0xffff, 0xf800, 0x07e0},
                                      {0xffff, 0xf800, 0x07e0},
                                      {0xf800, 0x07e0, 0x0000},
                                      {0xffdf, 0x2945, 0x0000}
                                    }; 
  float SET_CORRECTION_FACTOR_CH[3] = {15.5502, 15.5502, 15.5502};  //Коррекция амперметра
  bool IS_WIFI                      = true;                         //WI-FI включен/выключен
  char PASSWORD[64]                 = "12345678"; 
  uint8_t CRC;
};
