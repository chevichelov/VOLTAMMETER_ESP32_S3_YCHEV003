#pragma once
#include <Arduino.h>

class TO  {
  public:
    bool IS_CLEAR_DIRECTORY         = true;                             //Защита от двойного клика по кнопке очистки SD карты

    //Функция аналог функции MAP, но в отличии от оригинала умеет работать с типом данных FLOAT
    uint16_t MAPFLOAT(float VALUE, uint16_t MININ, uint16_t MAXIN, uint16_t MINOUT, uint16_t MAXOUT) {
      return (float)(VALUE - MININ) * (MAXOUT - MINOUT) / (float)(MAXIN - MININ) + MINOUT;
    }

    //Функция затирает предыдущие показания пробелами 
    char* DISPLAY_TEXT(float DATA, uint8_t COUNT, uint8_t FLOAT)          
    {
      static char DATA_RESULT[20];                                        //Объявляем переменную
      char DATA_DISPLAY[20];                                              //Объявляем переменную
      dtostrf(DATA, COUNT, FLOAT, DATA_DISPLAY);                          //Конвертируем показания в привычные глазу данные для дальнейшего вывода на экран
    
      uint8_t LEN = COUNT - (strlen(DATA_DISPLAY) - 1);                   //Узнаём длину полученных данных
      
      for(uint8_t i = 0; i < LEN; ++i)                                    //Вычисляем сколько пробелов не хватает
        strcpy(DATA_RESULT, " ");                                         //Создаём строку из недостающих пробелов
      
      strcat(DATA_RESULT, DATA_DISPLAY);                                  //Добавляем недостающие пробелы
      
      return DATA_RESULT;                                                 //Отдаём результат
    }

    //Функция выводит дату на экран
    String DISPLAY_DATE(uint8_t DATA)                                     
    {
      String DATE_RESULT = String(DATA);                                  //Конвертируем число в строку
      if (DATE_RESULT.length() == 1)                                      //Если число меньше 10, добавляем 0 перед числом
        DATE_RESULT = "0" + DATE_RESULT;
      return DATE_RESULT;                                                 //Выводим результат
    }

    //Функция конвертирует цвет из RGB в RGB16
    uint16_t RGB_TO_RGB16(uint8_t R, uint8_t G, uint8_t B)                
    {
      return ((R & 0xF8)<<8) | ((G & 0xFC)<<3) | ((B & 0xF8)>>3);
    }

    //Функция - аналог функции сплит
    uint8_t SPLIT(String TEXT, uint8_t POSITION)                          
    {
      uint16_t COUNT    = TEXT.length();
      uint8_t x         = 0, y = 0;
      for (uint8_t i=0; i < COUNT; i++)
        if(TEXT.charAt(i) == ',' || i == COUNT - 1)
        { 
          if (POSITION == y)
            return strtoul(TEXT.substring(x, i == COUNT - 1 ? i + 1 : i).c_str(), NULL, 0);
          ++y;
          x = i + 1;
        }
      return 0;
    }

     //Функция расчёта палитры
    uint16_t PALETTE(uint16_t NUMBER) {
      if (NUMBER <= 255)
        return ((255 & 0xF8)<<8) | ((NUMBER & 0xFC)<<3) | ((0 & 0xF8)>>3);
      else if (NUMBER > 255 && NUMBER <= 510) 
        return ((510 - NUMBER & 0xF8)<<8) | ((255 & 0xFC)<<3) | ((0 & 0xF8)>>3);
      else if (NUMBER > 510 && NUMBER <= 765)
        return ((0 & 0xF8)<<8) | ((255 & 0xFC)<<3) | ((NUMBER - 510 & 0xF8)>>3);
      else if (NUMBER > 765 && NUMBER <= 1020)
        return ((0 & 0xF8)<<8) | ((1020 - NUMBER & 0xFC)<<3) | ((255 & 0xF8)>>3);
      else if (NUMBER > 1020 && NUMBER <= 1275)
        return ((NUMBER - 1020 & 0xF8)<<8) | ((0 & 0xFC)<<3) | ((255 & 0xF8)>>3);
      else if (NUMBER > 1275 && NUMBER <= 1530)
        return ((255 & 0xF8)<<8) | ((0 & 0xFC)<<3) | ((1530 - NUMBER & 0xF8)>>3);  
      return 0;
    }

    //Функция расчёта палитры для RGB светодиода
    static uint32_t RGB_LED(uint16_t NUMBER) {
      if (NUMBER <= 255)
        return ((uint32_t)255 << 16) | ((uint32_t)NUMBER << 8) | 0;
      else if (NUMBER > 255 && NUMBER <= 510) 
        return ((uint32_t)(510 - NUMBER) << 16) | ((uint32_t)255 << 8) | 0;
      else if (NUMBER > 510 && NUMBER <= 765)
        return ((uint32_t)0 << 16) | ((uint32_t)255 << 8) | NUMBER - 510;
      else if (NUMBER > 765 && NUMBER <= 1020)
        return ((uint32_t)0 << 16) | ((uint32_t)(1020 - NUMBER) << 8) | 255;
      else if (NUMBER > 1020 && NUMBER <= 1275)
        return ((uint32_t)(NUMBER - 1020) << 16) | ((uint32_t)0 << 8) | 255;
      else if (NUMBER > 1275 && NUMBER <= 1530)
        return ((uint32_t)255 << 16) | ((uint32_t)0 << 8) | (1530 - NUMBER); 
      return 0;
    }

    //Получаем содержимое файла
    bool IS_FILE(String NAME)                                    
    {
      if (SD.exists("/" + NAME))
        return true;
      return false;
    }

    //Очищаем папку дата
    void CLEAR_DIRECTORY(fs::FS &fs)                                          
    {
      fs::File ROOT = fs.open("/");
      if (ROOT.isDirectory())
        while(true)
        {
          fs::File ENTRY =  ROOT.openNextFile();
          if (!ENTRY) 
            break;
          SD.remove("/" + String(ENTRY.name()));
          ENTRY.close();
        }
      ROOT.close();
      IS_CLEAR_DIRECTORY = true;
    }

    //Выводим информацию о списке файлов в папке
    String LIST_DIRECTORY(fs::FS &fs)                                       
    {
      String DATA   = "";
      fs::File ROOT = fs.open("/");
      if (ROOT.isDirectory())
        while(true)
        {
          fs::File ENTRY =  ROOT.openNextFile();
          if (!ENTRY) 
            break;
          if (ENTRY.size() > 0)
          {
            String DATE = ENTRY.name();
            DATE.remove(13);
            DATE.replace("_", "-");
            DATE[10] = ' ';
            DATA = ", {\"NAME\":\"" + String(ENTRY.name()) + "\", \"SIZE\":\"" + (ENTRY.size() / 1048576 > 0 ? String(ENTRY.size() / 1048576.0f) + "MB" : ENTRY.size() / 1024 > 0 ? String(ENTRY.size() / 1024.0f) + "KB" : String(ENTRY.size()) + "B") + "\", \"DATE\": \"" + DATE + "\", \"DOWNLOAD\": \"" + String(ENTRY.name()) + "\"}" + DATA; 
          }
          ENTRY.close();
        }
      ROOT.close();
      DATA.remove(0, 2);
      DATA = "[" + DATA + "]";
      return DATA;
    }

};
