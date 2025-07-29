#pragma once
#include <Arduino.h>

class DATA  {
  public: 
  uint8_t CHANNEL                 = 0;            //Номер канала
  uint8_t MENU                    = 0;            //Пункт меню
  uint8_t MENU_LAST               = 0;            //Предыдущий пункт меню
  bool CLICK_ONE                  = true;

  float VOLTAGES[3][661];                         //График Вольт
  float CURRENTS[3][661];                         //График Ампер
  float WATT[3][661];                             //График Ватт
  uint32_t TIME[3];
  bool IS_CARD                    = false;        //Инициализация SD карты
  
  uint16_t NUMBER                 = 0;            //Значение текущего измерения
  uint16_t CURSOR[2]              = {40, 40};     //Курсор

  uint32_t MATRIX_TIME            = 0;            //Защита от двойного клика по кнопке очистки данных
  bool MATRIX_DATA[12];                           //Матрица состояния клавиатуры   

  uint8_t SELECT_COLOR_SAVE[2]    = {0, 0};       //Вспомогательные переменные для выбора цвета
  uint8_t COLOR[3]                = {0, 0, 0};    //Вспомогательные переменные для выбора цвета
  uint8_t COUNT_COLOR_DOWN[3]     = {0, 0, 0};    //Вспомогательные переменные для выбора цвета
  uint8_t SELECT_COLOR            = 0;            //Вспомогательные переменные для выбора цвета
  bool IS_SELECT_COLOR            = false;        //Вспомогательные переменные для выбора цвета
};
