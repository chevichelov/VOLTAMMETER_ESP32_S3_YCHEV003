#include <GT911.h>
#include <Arduino_GFX_Library.h>
#include <INA226_WE.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <CRC8.h>
#include <CRC.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <esp_io_expander.hpp>
#include "Button.h" 
#include "Data.h"
#include "Save.h"
#include "Files.h"
#include "Convert.h"
#include "Config.h"
#include "To.h"
#include "Icons.h"
#include "Fonts/arialmt.h"
#include "Fonts/arialmt16.h"
#include "Fonts/arialmt18.h"
#include "Fonts/arialmt24.h"


TO TO;
DATA DATA;
SAVE CRC_SAVE;
SAVE SAVE;
CONVERT CONVERT;
CONFIG CONFIG;

IPAddress IP(192,168,0,1);
IPAddress GATEWAY(192,168,0,1);
IPAddress SUBNET(255,255,255,0);
AsyncWebServer SERVER(80);

RTC_DS3231 RTC;
GT911 TOUCH;

INA226_WE INA226_CH1 = INA226_WE(CONFIG.INA226_CH1);
INA226_WE INA226_CH2 = INA226_WE(CONFIG.INA226_CH2);
INA226_WE INA226_CH3 = INA226_WE(CONFIG.INA226_CH3);



Arduino_ESP32RGBPanel* rgbpanel = new Arduino_ESP32RGBPanel(
  5 /* DE */,  3 /* VSYNC */,  46 /* HSYNC */,  7 /* PCLK */,
  1 /* R0 */,  2 /* R1 */,  42 /* R2 */,  41 /* R3 */,  40 /* R4 */,
  39 /* G0 */,  0 /* G1 */,  45 /* G2 */,  48 /* G3 */,  47 /* G4 */,  21 /* G5 */,
  14 /* B0 */,  38 /* B1 */,  18 /* B2 */,  17 /* B3 */,  10 /* B4 */,
  0 /* hsync_polarity */, 40 /* hsync_front_porch */, 48 /* hsync_pulse_width */, 88 /* hsync_back_porch */,
  0 /* vsync_polarity */, 13 /* vsync_front_porch */, 3 /* vsync_pulse_width */, 32 /* vsync_back_porch */,
  1 /* pclk_active_neg */, 16000000 /* prefer_speed */
);


Arduino_RGB_Display* GFX = new Arduino_RGB_Display(
  800 /* width */,  480 /* height */,  rgbpanel,  0 /* rotation */,  true /* auto_flush */
);

Arduino_Canvas_Indexed *CANVAS = new Arduino_Canvas_Indexed(720, 480, GFX, 0, 0, 0, 0);

esp_expander::CH422G *expander = new esp_expander::CH422G(CONFIG.EXAMPLE_I2C_SCL_PIN, CONFIG.EXAMPLE_I2C_SDA_PIN, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS);


BUTTON MENU[6]                    = {                       //Кнопки меню
                                      {720, 0, 80, 80},
                                      {720, 80, 80, 80},
                                      {720, 160, 80, 80},
                                      {720, 240, 80, 80},
                                      {720, 320, 80, 80},
                                      {720, 400, 80, 80} 
                                   };
BUTTON BUTTON_CH_ACTIVE[3]        = {                       //Кнопки включения/выключения записи на SD карту
                                      {100, 50, 110, 50},
                                      {340, 50, 110, 50},
                                      {580, 50, 110, 50}
                                    };
BUTTON BUTTON_SELECT_CH_LEFT[3]   = {                       //Кнопки переключения профилей
                                      {600, 45, 40, 40},
                                      {600, 225, 40, 40},
                                      {600, 355, 40, 40}
                                    };
BUTTON BUTTON_SELECT_CH_RIGHT[3]  = {                       //Кнопки переключения профилей
                                      {670, 45, 40, 40},
                                      {670, 225, 40, 40},
                                      {670, 355, 40, 40}
                                    };
BUTTON BUTTON_SELECT_LIMIT[2]     = {                       //Кнопки выбора лимитов
                                      {20, 140, 255, 70},
                                      {320, 140, 230, 70}
                                    };
                                    
BUTTON BUTTON_LIMIT(600, 160, 110, 50);                     //Кнопка включение/выключения режима ограничения
BUTTON BUTTON_WIFI(130, 350, 110, 50);                      //Кнопка включение/выключения WI-FI
BUTTON BUTTON_CLEAR_DIRECTORY(500, 286, 180, 30);           //Кнопка очистки SD карты
BUTTON BUTTON_WIPE_DATA(500, 160, 180, 80);                 //Кнопка сброса устройства до заводских настроек

BUTTON BUTTON_INVERSION(5, 405, 60, 60);


                                    
//Получаем данные из EEPROM
void EEPROM_GET()                                                                       
{
  EEPROM.begin(CONFIG.EEPROM_LIMIT);
  EEPROM.get(0, CRC_SAVE);
  EEPROM.end();
}

//Сохраняем данные в EEPROM
void EEPROM_SAVE()                                                                      
{
  EEPROM.begin(CONFIG.EEPROM_LIMIT);
  SAVE.CRC = calcCRC8((uint8_t*)&SAVE, sizeof(SAVE) - 1);
  EEPROM.put(0, SAVE);
  EEPROM.commit();
  EEPROM.end();
}

//Очищаем EEPROM
void EEPROM_CLEAR()                                                                      
{
  EEPROM.begin(CONFIG.EEPROM_LIMIT);
  SAVE.CRC = 0;
  EEPROM.put(0, SAVE);
  EEPROM.commit();
  EEPROM.end();
}



void setup(void)
{
  Serial.begin(115200);
  const __FlashStringHelper* OK = F("OK");                      //Экономим оперативную память и сохраняем во флеш память
  const __FlashStringHelper* NO = F("NO");                      //Экономим оперативную память и сохраняем во флеш память
  
  GFX->begin();
  CANVAS->begin(GFX_SKIP_OUTPUT_BEGIN);
  
  GFX->fillScreen(SAVE.COLOR[4][1]);
  GFX->setTextColor(SAVE.COLOR[4][0]);
  GFX->setCursor(200, 10);
  GFX->println(F("youtube.com/@chevichelov"));
  GFX->print(F("Display..............................................................."));
  GFX->println(OK);
  
  GFX->print(F("SD..............................................................."));
  expander->init();
  expander->begin();
  expander->enableAllIO_Output();
  expander->digitalWrite(CONFIG.TP_RST , HIGH);
  expander->digitalWrite(CONFIG.LCD_RST , HIGH);
  expander->digitalWrite(CONFIG.LCD_BL , HIGH);
  expander->digitalWrite(CONFIG.SD_CS, LOW);
  expander->digitalWrite(CONFIG.USB_SEL, LOW);
  SPI.setHwCs(false);
  SPI.begin(CONFIG.SD_CLK, CONFIG.SD_MISO, CONFIG.SD_MOSI, CONFIG.SD_SS);
  if (!SD.begin(CONFIG.SD_SS)) {
    GFX->println(NO);
    SAVE.IS_ACTIVE[0] = DATA.IS_CARD;
    SAVE.IS_ACTIVE[1] = DATA.IS_CARD;
    SAVE.IS_ACTIVE[2] = DATA.IS_CARD;
  }
  else
  {
    GFX->println(OK);
    DATA.IS_CARD = true;
  }
  expander->del();
  
  GFX->print(F("CARD..............................................................."));
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE)
    GFX->println("NONE");
  else if(cardType == CARD_MMC)
    GFX->println("MMC");
  else if(cardType == CARD_SD)
    GFX->println("SDSC");
  else if(cardType == CARD_SDHC)
    GFX->println("SDHC");
  else
    GFX->println("UNKNOWN");
 
  
  pinMode(CONFIG.PIN_ANALOG_READ, OUTPUT);
  digitalWrite(CONFIG.PIN_ANALOG_READ, LOW);
  
  GFX->print(F("TOUCH..............................................................."));
  if (!TOUCH.begin(-1, -1, GT911_I2C_ADDR_28, 400000))
  {
    if (!TOUCH.begin(-1, -1, GT911_I2C_ADDR_BA, 400000))
    {
      GFX->println(NO);
    }
    else
      GFX->println(OK);
  }
  else
    GFX->println(OK);

  GFX->print(F("EEPROM..............................................................."));
  EEPROM_GET();
  if (calcCRC8((uint8_t*)&CRC_SAVE, sizeof(CRC_SAVE)) == 0)
  {
    SAVE = CRC_SAVE;
    GFX->println(OK);
  }
  else
    GFX->println(NO);
  

  GFX->print(F("INA226 CH1..........................................................."));
  if (INA226_CH1.init() == 1)
  {
    INA226_CH1.setConversionTime(CONV_TIME_8244);                     //Время конверсии в микросекундах (140,204,332,588,1100,2116,4156,8244)8244µs=8.244 ms
    INA226_CH1.setAverage(AVERAGE_4);                                 //Среднее количество чтений n раз (1,4,16,64,128,256,512,1024)
    INA226_CH1.setMeasureMode(CONTINUOUS);
    INA226_CH1.setCorrectionFactor(SAVE.SET_CORRECTION_FACTOR_CH[1]);
    GFX->println(OK);
  }
  else
    GFX->println(NO);

  GFX->print(F("INA226 CH2..........................................................."));
  if (INA226_CH2.init() == 1)
  {
    INA226_CH2.setConversionTime(CONV_TIME_8244);                     //Время конверсии в микросекундах (140,204,332,588,1100,2116,4156,8244)8244µs=8.244 ms
    INA226_CH2.setAverage(AVERAGE_4);                                 //Среднее количество чтений n раз (1,4,16,64,128,256,512,1024)
    INA226_CH2.setMeasureMode(CONTINUOUS);
    INA226_CH2.setCorrectionFactor(SAVE.SET_CORRECTION_FACTOR_CH[2]);
    GFX->println(OK);
  }
  else
    GFX->println(NO);

  GFX->print(F("INA226 CH3..........................................................."));
  if (INA226_CH3.init() == 1)
  {
    INA226_CH3.setConversionTime(CONV_TIME_8244);                     //Время конверсии в микросекундах (140,204,332,588,1100,2116,4156,8244)8244µs=8.244 ms
    INA226_CH3.setAverage(AVERAGE_4);                                 //Среднее количество чтений n раз (1,4,16,64,128,256,512,1024)
    INA226_CH3.setMeasureMode(CONTINUOUS);
    INA226_CH3.setCorrectionFactor(SAVE.SET_CORRECTION_FACTOR_CH[3]);
    GFX->println(OK);
  }
  else
    GFX->println(NO);

  GFX->print(F("RTC..............................................................."));
  if (!RTC.begin()) 
  {
    GFX->println(NO);
  }
  else
  {
    if(RTC.lostPower())
      RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    GFX->println(OK);
  }

  GFX->print(F("WI-FI..............................................................."));
  if (SAVE.IS_WIFI)
  {
    WiFi.softAP("youtube_com_chevichelov", SAVE.PASSWORD);
    WiFi.softAPConfig(IP, GATEWAY, SUBNET);

    SERVER.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/html; charset=utf-8", index_html);                                               //Главная страница
    });
    SERVER.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/html; charset=utf-8", settings_html);                                            //Страница настроек
    });
    SERVER.on("/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/css; charset=utf-8", style_css);                                                 //Файл стилей
    });
    SERVER.on("/log", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "application/json; charset=utf-8", TO.LIST_DIRECTORY(SD));                             //Какое пространство занято на SD карте
    });
    SERVER.on("/files", HTTP_GET, [](AsyncWebServerRequest *request){
      const char* PARAM_FILE = "file";
      if (request->hasParam(PARAM_FILE)) {
        if (TO.IS_FILE(request->getParam(PARAM_FILE)->value()))
        {
          request->send(SD, "/" + request->getParam(PARAM_FILE)->value(), "application/octet-stream", true);    //Отдаём файл с SD карты
        }
        else 
          request->send(404, "text/plain", F("404: Not found"));
      }
      else
        request->send(404, "text/plain", F("404: Not found"));
    });
    SERVER.on("/loadsetting", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "application/json; charset=utf-8", "{\"PASSWORD\":\"" + String(SAVE.PASSWORD) + "\", \"CH1\":\"" + String(SAVE.SET_CORRECTION_FACTOR_CH[0], 4) + "\", \"CH2\":\"" + String(SAVE.SET_CORRECTION_FACTOR_CH[1], 4) + "\", \"CH3\":\"" + String(SAVE.SET_CORRECTION_FACTOR_CH[2], 4) + "\"}");
    });                                                                                                         //Данные о настройках
    SERVER.on("/setting", HTTP_GET, [](AsyncWebServerRequest *request){
      const char* PARAM_PASSWORD = "password";
      const char* PARAM_TIME = "time";
      const char* PARAM_CH1 = "ch1";
      const char* PARAM_CH2 = "ch2";
      const char* PARAM_CH3 = "ch3";
      if (request->hasParam(PARAM_PASSWORD)) 
      {
        if (request->getParam(PARAM_PASSWORD)->value().length() > 63)
        {
          request->send(400, "text/plain; charset=utf-8", "ERROR_LENGTH_PASSWORD");
          return;
        }
        memset(SAVE.PASSWORD, 0, (sizeof(SAVE.PASSWORD)/sizeof(char)) - 1);
        strncpy(SAVE.PASSWORD, request->getParam(PARAM_PASSWORD)->value().c_str(), request->getParam(PARAM_PASSWORD)->value().length());
      }
      if (request->hasParam(PARAM_TIME)) 
      {
        String PARAM_DATE = request->getParam(PARAM_TIME)->value(); 
        RTC.adjust(DateTime(atoi(PARAM_DATE.substring(0, 4).c_str()), atoi(PARAM_DATE.substring(5, 7).c_str()), atoi(PARAM_DATE.substring(8, 10).c_str()), atoi(PARAM_DATE.substring(11, 13).c_str()), atoi(PARAM_DATE.substring(14, 16).c_str()), atoi(PARAM_DATE.substring(17, 19).c_str())));
      }
      if (request->hasParam(PARAM_CH1)) 
        SAVE.SET_CORRECTION_FACTOR_CH[0] = atof(request->getParam(PARAM_CH1)->value().c_str());
      if (request->hasParam(PARAM_CH2)) 
        SAVE.SET_CORRECTION_FACTOR_CH[1] = atof(request->getParam(PARAM_CH2)->value().c_str());
      if (request->hasParam(PARAM_CH3)) 
        SAVE.SET_CORRECTION_FACTOR_CH[2] = atof(request->getParam(PARAM_CH3)->value().c_str());
      EEPROM_SAVE();
      request->send(200, "text/plain; charset=utf-8", "OK");
      delay(500);
      ESP.restart();
    }); 
    SERVER.onNotFound([](AsyncWebServerRequest *request){
      request->send(404, "text/plain", F("404: Not found"));                                                    //Страница не найдена
    });
    SERVER.begin();  
    GFX->println(OK);
  }
  else
    GFX->println(NO);
  GFX->fillScreen(SAVE.COLOR[4][1]);
  MAIN_MENU();

}


//Основное меню
void MAIN_MENU()
{
  uint16_t X = 0;
  for(uint8_t i = 0; i <= 5; ++i)
  {
    if (DATA.MENU_LAST == i)
    {
      X = i * 80;
      GFX->fillRect(720,  X, 80, 80, SAVE.COLOR[4][1]);
    }
    if (DATA.MENU == i)
      GFX->fillRect(720, i * 80, 80, 80, 0x3596);
    else
      GFX->drawRect(720, i * 80, 80, 80, 0x39e8);
  }
  GFX->drawRect(720, 320, 80, 80, 0x39e8);
  GFX->drawRect(720, 400, 80, 80, 0x39e8);
  GFX->drawBitmap(720, 0, HOME_ICON, 80, 80, SAVE.COLOR[4][0]);
  GFX->setTextColor(SAVE.COLOR[4][0]);
  GFX->setFont(&arialmt18pt7b);
  GFX->setCursor(730, 130);
  GFX->print(F("CH1"));
  GFX->setCursor(730, 210);
  GFX->print(F("CH2"));
  GFX->setCursor(730, 290);
  GFX->print(F("CH3"));
  GFX->drawBitmap(720, 320, PALETTE_ICON, 80, 80, SAVE.COLOR[4][0]);
  GFX->drawBitmap(720, 400, SETTING_ICON, 80, 80, SAVE.COLOR[4][0]);
  DATA.CLICK_ONE = false;
  DATA.MENU_LAST = DATA.MENU;
  
}

//Экранная клавиатура
void KEYBOARD()
{
  CANVAS->setFont(&arialmt24pt7b);
  CANVAS->setTextColor(SAVE.COLOR[4][0]);
  char BATTON_NAME[13] = {'1', '2', '3', '<', '4', '5', '6', '0', '7', '8', '9', 'O', 'K'};
  uint8_t BATTON_NAMBER = 0;
  for(uint8_t y = 0; y <= 2; ++y)
    for(uint8_t x = 0; x <= 3; ++x)
    {
      CANVAS->fillRect(20 + x * 180, 230 + y * 85, 150, 70, DATA.MATRIX_DATA[BATTON_NAMBER] && BATTON_NAMBER < 11 ? 0xC69B : 0x39e8);
      if (DATA.MATRIX_DATA[BATTON_NAMBER])
        DATA.MATRIX_DATA[BATTON_NAMBER] = false;
      CANVAS->drawRect(20 + x * 180, 230 + y * 85, 150, 70, 0xCE9A);
      CANVAS->setCursor((BATTON_NAMBER == 11 ? 70 : 80) + x * 180, 280 + y * 85);
      CANVAS->print(BATTON_NAME[BATTON_NAMBER]);
      ++BATTON_NAMBER;
    }
    CANVAS->print(BATTON_NAME[BATTON_NAMBER]);
}

//Переключатель
void SWITCH(uint16_t X, uint16_t Y, bool IS_PRESSED)
{
  CANVAS->drawRect(X, Y, 110, 50, IS_PRESSED ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
  CANVAS->fillRect(IS_PRESSED ? X + 68 : X + 2, Y + 2, 40, 46, IS_PRESSED ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
  CANVAS->setCursor(IS_PRESSED ? X + 18 : X + 48, Y + 35);
  CANVAS->print(IS_PRESSED ? F("ON") : F("OFF"));
}

//Кнопка с номером
void RECT(uint16_t X, uint16_t Y, uint8_t NUMBER, bool IS_PRESSED)
{
  CANVAS->fillRect(X, Y, 46, 46, IS_PRESSED ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
  CANVAS->setCursor(X + 15, Y + 35);
  CANVAS->print(NUMBER);
}

//Главная страница
void MAIN()
{ 
  CANVAS->fillRect(0, 0, 720, 40, 0x39e8);
  CANVAS->setFont(&arialmt16pt7b);
  CANVAS->setTextColor(SAVE.COLOR[4][0]);
  CANVAS->setCursor(20, 30);
  CANVAS->print(F("DATE: "));
  char DATE[20] = "DD.MM.YYYY hh:mm:ss";
  RTC.now().toString(DATE);
  CANVAS->print(DATE);
  if (SAVE.IS_WIFI)
    CANVAS->drawBitmap(675, 5, WIFI_ICON, 30, 30, 0xCE9A);

  CANVAS->setFont(&arialmt24pt7b);
  CANVAS->setCursor(20, 200);
  CANVAS->print(F("OFF: "));
  CANVAS->print(SAVE.LIMIT[0]);
  CANVAS->print(F("V"));
  CANVAS->drawFastHLine(20, 210, 260, SAVE.IS_LIMIT ? 0x07e0 : 0xCE9A);
  CANVAS->setCursor(320, 200);
  CANVAS->print(F("ON: "));
  CANVAS->print(SAVE.LIMIT[1]);
  CANVAS->print(F("V"));
  CANVAS->drawFastHLine(320, 210, 230, SAVE.IS_LIMIT ? 0x07e0 : 0xCE9A);
  CANVAS->setFont(&arialmt16pt7b);
  SWITCH(600, 160, SAVE.IS_LIMIT);

  if (SAVE.IS_SELECT_LIMIT)
    KEYBOARD();
    
  for(uint8_t i = 0; i < (SAVE.IS_SELECT_LIMIT ? 1 : 3); ++i)
  {
    CANVAS->setFont(&arialmt36pt7b);
    CANVAS->setTextColor(SAVE.COLOR[i][0]);
    CANVAS->setCursor(20, 100 + i * 130 + (i ? 50 : 0));
    CANVAS->print(DATA.VOLTAGES[i][DATA.NUMBER - 1]);
    CANVAS->setFont(&arialmt24pt7b);
    CANVAS->print(F("V"));

    CANVAS->setCursor(600, 80 + i * 130 + (i ? 50 : 0));
    CANVAS->setTextColor(SAVE.COLOR[4][0]);
    if(BUTTON_SELECT_CH_LEFT[i].IS_PRESSED)
    {
      CANVAS->fillCircle(615, 63 + i * 130 + (i ? 50 : 0), 20, 0x39e8);
      BUTTON_SELECT_CH_LEFT[i].IS_PRESSED = false;
    }
    CANVAS->print(F("< "));
    CANVAS->setTextColor(0x07e0);
    CANVAS->print(SAVE.ACTIV_NAMBER[i] + 1);
    CANVAS->setTextColor(SAVE.COLOR[4][0]);
    if(BUTTON_SELECT_CH_RIGHT[i].IS_PRESSED)
    {
      CANVAS->fillCircle(690, 63 + i * 130 + (i ? 50 : 0), 20, 0x39e8);
      BUTTON_SELECT_CH_RIGHT[i].IS_PRESSED = false;
    }
    CANVAS->print(F(" >"));

    CANVAS->setFont(&arialmt18pt7b);
    CANVAS->setTextColor(SAVE.COLOR[i][1]);
    CANVAS->setCursor(275, 70 + i * 130 + (i ? 50 : 0));
    CANVAS->print(DATA.CURRENTS[i][DATA.NUMBER - 1], 3);
    CANVAS->setFont(&arialmt16pt7b);
    CANVAS->print(F("A"));
    CANVAS->setCursor(275, 100 + i * 130 + (i ? 50 : 0));
    CANVAS->print(SAVE.CURRENT_HOUR[i][SAVE.ACTIV_NAMBER[i]], 3);
    CANVAS->print(F("Ah"));
  
    CANVAS->setFont(&arialmt18pt7b);
    CANVAS->setTextColor(SAVE.COLOR[i][2]);
    CANVAS->setCursor(440, 70 + i * 130 + (i ? 50 : 0));
    CANVAS->print(DATA.WATT[i][DATA.NUMBER - 1], 3);
    CANVAS->setFont(&arialmt16pt7b);
    CANVAS->print(F("W"));
    CANVAS->setCursor(440, 100 + i * 130 + (i ? 50 : 0));
    CANVAS->print(SAVE.WATT_HOUR[i][SAVE.ACTIV_NAMBER[i]], 3);
    CANVAS->print(F("Wh"));
  
    CANVAS->setTextColor(SAVE.COLOR[4][0]);
   
    CANVAS->setCursor(20, 140 + i * 130 + (i ? 50 : 0));
    CANVAS->print(F("CH"));
    CANVAS->print(i + 1);
    CANVAS->print(F(": VOLTAGE"));
    CANVAS->setCursor(275, 140 + i * 130 + (i ? 50 : 0));
    CANVAS->print(F("CURRENT"));
    CANVAS->setCursor(440, 140 + i * 130 + (i ? 50 : 0));
    CANVAS->print(F("POWER"));

    CANVAS->drawBitmap(SAVE.IS_ACTIVE[i] ? 605 : 570, 121 + i * 130 + (i ? 50 : 0), POINT_ICON, 20, 20, SAVE.IS_ACTIVE[i] ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
    CANVAS->setCursor(SAVE.IS_ACTIVE[i] ? 640 : 605, 140 + i * 130 + (i ? 50 : 0));
    CANVAS->setTextColor(SAVE.IS_ACTIVE[i] ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
    CANVAS->print(SAVE.IS_ACTIVE[i] ? "REC" : "NO REC");
  }
}

//График
void CHART()
{
  CANVAS->setFont(&arialmt36pt7b);
  CANVAS->setTextColor(SAVE.COLOR[DATA.CHANNEL][0]);
  CANVAS->setCursor(40, 55);
  CANVAS->print(DATA.VOLTAGES[DATA.CHANNEL][DATA.NUMBER - 1]);
  CANVAS->setFont(&arialmt24pt7b);
  CANVAS->print(F("V"));
  
  CANVAS->setFont(&arialmt18pt7b);
  CANVAS->setTextColor(SAVE.COLOR[DATA.CHANNEL][1]);
  CANVAS->setCursor(275, 35);
  CANVAS->print(DATA.CURRENTS[DATA.CHANNEL][DATA.NUMBER - 1], 3);
  CANVAS->setFont(&arialmt16pt7b);
  CANVAS->print(F("A"));
  CANVAS->setCursor(275, 65);
  CANVAS->print(SAVE.CURRENT_HOUR[DATA.CHANNEL][SAVE.ACTIV_NAMBER[DATA.CHANNEL]], 3);
  CANVAS->print(F("Ah"));

  CANVAS->setFont(&arialmt18pt7b);
  CANVAS->setTextColor(SAVE.COLOR[DATA.CHANNEL][2]);
  CANVAS->setCursor(440, 35);
  CANVAS->print(DATA.WATT[DATA.CHANNEL][DATA.NUMBER - 1], 3);
  CANVAS->setFont(&arialmt16pt7b);
  CANVAS->print(F("W"));
  CANVAS->setCursor(440, 65);
  CANVAS->print(SAVE.WATT_HOUR[DATA.CHANNEL][SAVE.ACTIV_NAMBER[DATA.CHANNEL]], 3);
  CANVAS->print(F("Wh"));


  CANVAS->drawBitmap(SAVE.IS_ACTIVE[DATA.CHANNEL] ? 590 : 570, 16, POINT_ICON, 20, 20, SAVE.IS_ACTIVE[DATA.CHANNEL] ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
  CANVAS->setCursor(SAVE.IS_ACTIVE[DATA.CHANNEL] ? 625 : 605, 35);
  CANVAS->setTextColor(SAVE.IS_ACTIVE[DATA.CHANNEL] ? SAVE.COLOR[3][1] : SAVE.COLOR[3][0]);
  CANVAS->print(SAVE.IS_ACTIVE[DATA.CHANNEL] ? F("REC") : F("NO REC"));
  
  CANVAS->setTextColor(SAVE.COLOR[4][0]);
  CANVAS->setCursor(580, 90);
  CONVERT.TIME_TO_DATE(SAVE.SET_MILLISECOND[DATA.CHANNEL][SAVE.ACTIV_NAMBER[DATA.CHANNEL]]);
  if (CONVERT.H < 10)
    CANVAS->print(F("0"));
  CANVAS->print(CONVERT.H);
  CANVAS->print(F(":"));
  if (CONVERT.m < 10)
    CANVAS->print(F("0"));
  CANVAS->print(CONVERT.m);
  CANVAS->print(F(":"));
  if (CONVERT.s < 10)
    CANVAS->print(F("0"));
  CANVAS->print(CONVERT.s, DEC);

  CANVAS->setCursor(40, 95);
  CANVAS->print(F("CH"));
  CANVAS->print(DATA.CHANNEL + 1);
  CANVAS->print(F(": VOLTAGE"));
  CANVAS->setCursor(275, 95);
  CANVAS->print(F("CURRENT"));
  CANVAS->setCursor(440, 95);
  CANVAS->print(F("POWER"));
 
  CANVAS->setFont();
  for (uint8_t  i = 0; i <= 4; ++i)
  {
    CANVAS->drawLine(40, 120 + i * 80, 700, 120 + i * 80, 0x632d);
    CANVAS->drawLine(40 + i * 160, 100, 40 + i * 160, 440, 0x632d);
    if (i < 4)
    {
      CANVAS->setCursor(190 + i * 160, 460);
      CANVAS->print((i + 1) * 160);
    }
  }
  uint16_t MAX_VALUE = 0, MIN_VALUE = 999;
  for (uint16_t  i = 0; i < DATA.NUMBER; ++i)
  {
    if (i + 1 < DATA.NUMBER)
    {
      MAX_VALUE = max(MAX_VALUE, (uint16_t)ceil(DATA.VOLTAGES[DATA.CHANNEL][i]));
      MAX_VALUE = max(MAX_VALUE, (uint16_t)ceil(DATA.CURRENTS[DATA.CHANNEL][i]));
      MAX_VALUE = max(MAX_VALUE, (uint16_t)ceil(DATA.VOLTAGES[DATA.CHANNEL][i + 1]));
      MAX_VALUE = max(MAX_VALUE, (uint16_t)ceil(DATA.CURRENTS[DATA.CHANNEL][i + 1]));
      
      MIN_VALUE = min(MIN_VALUE, (uint16_t)floor(DATA.VOLTAGES[DATA.CHANNEL][i]));
      MIN_VALUE = min(MIN_VALUE, (uint16_t)floor(DATA.CURRENTS[DATA.CHANNEL][i]));
      MIN_VALUE = min(MIN_VALUE, (uint16_t)floor(DATA.VOLTAGES[DATA.CHANNEL][i + 1]));
      MIN_VALUE = min(MIN_VALUE, (uint16_t)floor(DATA.CURRENTS[DATA.CHANNEL][i + 1]));
      
      CANVAS->drawLine(i+40, TO.MAPFLOAT(DATA.VOLTAGES[DATA.CHANNEL][i], MIN_VALUE, MAX_VALUE, 440, 120), i+41, TO.MAPFLOAT(DATA.VOLTAGES[DATA.CHANNEL][i + 1], MIN_VALUE, MAX_VALUE, 440, 120), SAVE.COLOR[DATA.CHANNEL][0]);
      CANVAS->drawLine(i+40, TO.MAPFLOAT(DATA.CURRENTS[DATA.CHANNEL][i], MIN_VALUE, MAX_VALUE, 440, 120), i+41, TO.MAPFLOAT(DATA.CURRENTS[DATA.CHANNEL][i + 1], MIN_VALUE, MAX_VALUE, 440, 120), SAVE.COLOR[DATA.CHANNEL][1]);
     }
  }

  for (uint8_t  i = 0; i <= 4; ++i)
  {
    CANVAS->setCursor(10, 120 + i * 80);
    CANVAS->print(i == 0 ? MAX_VALUE : i == 4 ? MIN_VALUE : (MAX_VALUE - MIN_VALUE) / 5 * (5 - i));
  }
 
  CANVAS->drawLine(DATA.CURSOR[0], 100, DATA.CURSOR[0], 450, 0xff60);
  CANVAS->setTextColor(0xff60);
  CANVAS->setCursor(10, 455);
  CANVAS->print(F("("));
  CANVAS->print(DATA.VOLTAGES[DATA.CHANNEL][DATA.CURSOR[0] - 40]);
  CANVAS->print(F(","));
  CANVAS->print(DATA.CURRENTS[DATA.CHANNEL][DATA.CURSOR[0] - 40]);
  CANVAS->print(F(","));
  CANVAS->print(DATA.WATT[DATA.CHANNEL][DATA.CURSOR[0] - 40]);
  CANVAS->print(F(","));
  CANVAS->print(DATA.CURSOR[0] - 40);
  CANVAS->print(F(")"));

  CANVAS->drawLine(DATA.CURSOR[1], 100, DATA.CURSOR[1], 450, 0x07e0);
  CANVAS->setTextColor(0x07e0);
  CANVAS->setCursor(10, 470);
  CANVAS->print(F("("));
  CANVAS->print(DATA.VOLTAGES[DATA.CHANNEL][DATA.CURSOR[1] - 40]);
  CANVAS->print(F(","));
  CANVAS->print(DATA.CURRENTS[DATA.CHANNEL][DATA.CURSOR[1] - 40]);
  CANVAS->print(F(","));
  CANVAS->print(DATA.WATT[DATA.CHANNEL][DATA.CURSOR[1] - 40]);
  CANVAS->print(F(","));
  CANVAS->print(DATA.CURSOR[1] - 40);
  CANVAS->print(F(")"));

  CANVAS->setTextColor(0xf800);
  CANVAS->setCursor(240, 460);
  CANVAS->print(F("T: "));
  CANVAS->print(abs(DATA.CURSOR[1] - DATA.CURSOR[0]));
}

//Выбор цветов
void PALETTES()
{
  if (DATA.IS_SELECT_COLOR)
  {
    CANVAS->fillRect(20, 20, 180, 180, TO.RGB_TO_RGB16(DATA.COLOR[0], DATA.COLOR[1], DATA.COLOR[2]));
    CANVAS->drawRect(20, 20, 180, 180, 0xffff - TO.RGB_TO_RGB16(DATA.COLOR[0], DATA.COLOR[1], DATA.COLOR[2]));
    CANVAS->setFont(&arialmt24pt7b);
    CANVAS->setCursor(220, 50);
    for(uint8_t i = 0; i <= 2; ++i)
    {
      CANVAS->print(i == 0 ? F("R: ") : i == 1 ? F(" G: ") : F(" B: "));
      CANVAS->print(DATA.COLOR[i]);
    }
    CANVAS->setCursor(220, 110);
    CANVAS->print(F("RGB565: 0x"));
    CANVAS->print(TO.RGB_TO_RGB16(DATA.COLOR[0], DATA.COLOR[1], DATA.COLOR[2]), HEX);
    KEYBOARD();
  }
  else
  {
    CANVAS->setTextColor(SAVE.COLOR[4][0]);
    CANVAS->setFont(&arialmt16pt7b);
    for(uint8_t y = 0; y <= 4; ++y)
      for(uint8_t x = 0; x <= 2; ++x)
      {
        if (x != 2 && y >= 3 || y < 3)
        {
          CANVAS->fillRect(5 + x * 250, 5 + y * 80, 60, 60, SAVE.COLOR[y][x]);
          CANVAS->drawRect(5 + x * 250, 5 + y * 80, 60, 60, 0xffff - SAVE.COLOR[y][x]);
          CANVAS->setCursor(75 + x * 250, 30 + y * 80);
          CANVAS->print(y < 3 ? F("CH") : y == 3 ? F("SWITCH") : y == 4 && x == 0 ? F("TEXT") : F("BACKGROUND"));
          if (y < 3)
            CANVAS->print(x + 1);
          if (y < 4)
          {
            CANVAS->setCursor(75 + x * 250, 60 + y * 80);
            CANVAS->print(x == 0 && y <= 2 ? F("VOLTAGE") : x == 1 && y <= 2 ? F("CURRENT") : x == 2 && y <= 2 ? F("WATT") : (x == 0 ? F("OFF") : F("ON")));
          }
        }
      }

      CANVAS->fillRect(5, 405, 60, 60, 0xffff - SAVE.COLOR[4][1]);
      CANVAS->drawRect(5, 405, 60, 60, 0xffff - SAVE.COLOR[4][1] / 2);
      CANVAS->setCursor(75, 430);
      CANVAS->print(F("INVERSION"));
      CANVAS->setCursor(75, 460);
      CANVAS->print(F("COLOR"));
  }
}

//Настройки
void SETTINGS()
{
  CANVAS->setFont(&arialmt16pt7b);
  CANVAS->setTextColor(SAVE.COLOR[4][0]);
  CANVAS->setCursor(20, 30);
  CANVAS->print(F("Recording to SD card:"));

  CANVAS->setCursor(20, 145);
  CANVAS->print(F("CLEAR PROFILE:"));


  CANVAS->fillRect(500, 160, 180, 80, 0xf800);
  CANVAS->setCursor(510, 210);
  CANVAS->print(F("WIPE DATA"));

  CANVAS->fillRect(500, 286, 180, 30, 0xf800);
  CANVAS->setCursor(520, 311);
  CANVAS->print(TO.IS_CLEAR_DIRECTORY ? F("CLEAR SD") : F("WAIT..."));

  for(uint8_t y = 0; y <= 2; ++y)
  {
    CANVAS->setCursor(20 + 240 * y, 85);
    CANVAS->print(F("CH"));
    CANVAS->print(y);
    SWITCH(100 + 240 * y, 50, SAVE.IS_ACTIVE[y]);
    
    CANVAS->setCursor(20, 195 + y * 55);
    CANVAS->print(F("CH"));
    CANVAS->print(y + 1);
    for(uint8_t x = 0; x <= 4; ++x)
      RECT(100 + x * 70, 160 + y * 55, x + 1, SAVE.WATT_HOUR[y][x] > 0);
  }
  
  CANVAS->setCursor(20, 385);
  CANVAS->print(F("WI-FI"));
  
  SWITCH(130, 350, SAVE.IS_WIFI);

  CANVAS->setCursor(310, 385);
  CANVAS->print(F("IP: "));
  CANVAS->print(IP);
  CANVAS->setCursor(20, 430);
  CANVAS->print(F("NET: youtube_com_chevichelov"));
  CANVAS->setCursor(20, 470);
  CANVAS->print(F("PASSWORD: ")); 
  CANVAS->print(SAVE.PASSWORD);
}


//Основная программа
void loop()
{
  uint8_t TOUCHS = TOUCH.touched(GT911_MODE_POLLING);
  CANVAS->fillScreen(SAVE.COLOR[4][1]);
  
  if (TOUCHS) 
  {
    uint16_t X, Y;
    GTPoint* POINT = TOUCH.getPoints();
    X = POINT[0].x;
    Y = POINT[0].y;

    if (DATA.MENU == 0)
    {
      if (SAVE.IS_SELECT_LIMIT)
      {
        uint8_t BATTON_NAME[13]  = {1, 2, 3, 98, 4, 5, 6, 0, 7, 8, 9, 99, 99};
        uint8_t BATTON_NAMBER   = 0;
        if (millis() - DATA.MATRIX_TIME >= 400)
          for(uint8_t y = 0; y <= 2; ++y)
            for(uint8_t x = 0; x <= 3; ++x)
            {
              if (X >= 20 + x * 180 && X <= 170 + x * 180 && Y >= 230 + y * 85 && Y <= 300 + y * 85)
              { 
                DATA.MATRIX_DATA[BATTON_NAMBER] = true;
                if (BATTON_NAME[BATTON_NAMBER] < 10)
                {   
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 0 || SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 4)
                    {
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = BATTON_NAME[BATTON_NAMBER];
                      if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 4)
                        SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] = 0;
                    }
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 1)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = SAVE.LIMIT[SAVE.SELECT_LIMIT] * 10 + BATTON_NAME[BATTON_NAMBER];
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 2)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = SAVE.LIMIT[SAVE.SELECT_LIMIT] + BATTON_NAME[BATTON_NAMBER] * 0.1;
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 3)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = SAVE.LIMIT[SAVE.SELECT_LIMIT] + BATTON_NAME[BATTON_NAMBER] * 0.01;
                    ++SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT];
                }
                else if (BATTON_NAME[BATTON_NAMBER] == 98)
                { 
                  if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 1)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = 0;
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 2)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = (int)(SAVE.LIMIT[SAVE.SELECT_LIMIT] / 10);
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 3)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = (int)SAVE.LIMIT[SAVE.SELECT_LIMIT];
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] == 4)
                      SAVE.LIMIT[SAVE.SELECT_LIMIT] = ((int)(SAVE.LIMIT[SAVE.SELECT_LIMIT] * 10)) / 10.0f ;
                    if (SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT] != 0)
                      --SAVE.COUNT_LIMIT_DOWN[SAVE.SELECT_LIMIT];
                }
                else if (BATTON_NAME[BATTON_NAMBER] == 99)
                {
                  SAVE.IS_SELECT_LIMIT  = false;
                  EEPROM_SAVE();
                }
                DATA.MATRIX_TIME  = millis();
              }
              ++BATTON_NAMBER;
            }
      }

      if (BUTTON_SELECT_LIMIT[0].IS_PRESS(X, Y))
      {
        SAVE.SELECT_LIMIT     = 0;
        SAVE.IS_SELECT_LIMIT  = true;
        EEPROM_SAVE();
      }
      if (BUTTON_SELECT_LIMIT[1].IS_PRESS(X, Y))
      {
        SAVE.SELECT_LIMIT     = 1;
        SAVE.IS_SELECT_LIMIT  = true;
        EEPROM_SAVE();
      }
      if (BUTTON_LIMIT.IS_PRESS(X, Y))
      {
        SAVE.IS_LIMIT = !SAVE.IS_LIMIT;
        EEPROM_SAVE();
      }

      if (BUTTON_SELECT_CH_LEFT[0].IS_PRESS(X, Y) && SAVE.ACTIV_NAMBER[0] > 0)
      {
        --SAVE.ACTIV_NAMBER[0];
        EEPROM_SAVE();
      }
      if (BUTTON_SELECT_CH_RIGHT[0].IS_PRESS(X, Y) && SAVE.ACTIV_NAMBER[0] < 4)
      {
        ++SAVE.ACTIV_NAMBER[0];
        EEPROM_SAVE();
      }
      if (BUTTON_SELECT_CH_LEFT[1].IS_PRESS(X, Y) && SAVE.ACTIV_NAMBER[1] > 0)
      {
        --SAVE.ACTIV_NAMBER[1];
        EEPROM_SAVE();
      }
      if (BUTTON_SELECT_CH_RIGHT[1].IS_PRESS(X, Y) && SAVE.ACTIV_NAMBER[1] < 4)
      {
        ++SAVE.ACTIV_NAMBER[1];
        EEPROM_SAVE();
      }
      if (BUTTON_SELECT_CH_LEFT[2].IS_PRESS(X, Y) && SAVE.ACTIV_NAMBER[2] > 0)
      {
        --SAVE.ACTIV_NAMBER[2];
        EEPROM_SAVE();
      }
      if (BUTTON_SELECT_CH_RIGHT[2].IS_PRESS(X, Y) && SAVE.ACTIV_NAMBER[2] < 4)
      {
        ++SAVE.ACTIV_NAMBER[2];
        EEPROM_SAVE();
      }
    }
    else if (DATA.MENU == 1 || DATA.MENU == 2 || DATA.MENU == 3)
    {
      if (X >= 40 && X <= 700)
          DATA.CURSOR[0] = X;
      if (POINT[1].x >= 40 && POINT[1].x <= 700)
          DATA.CURSOR[1] = POINT[1].x;  
    } 
    else  if (DATA.MENU == 4)
    {
      if (!DATA.IS_SELECT_COLOR)
      {
        if (millis() - DATA.MATRIX_TIME >= 400)
            for(uint8_t y = 0; y <= 4; ++y)
              for(uint8_t x = 0; x <= 2; ++x)
              {
                if (X >= 5 + x * 250 && X <= 250 + x * 250 && Y >= 5 + y * 80 && Y <= 80 + y * 80 && (x != 2 && y >= 3 || y < 3))
                {
                  DATA.COLOR[0]                             = ((((SAVE.COLOR[y][x] >> 11) & 0x1F) * 527) + 23) >> 6;
                  DATA.COLOR[1]                             = ((((SAVE.COLOR[y][x] >> 5) & 0x3F) * 259) + 33) >> 6;
                  DATA.COLOR[2]                             = (((SAVE.COLOR[y][x] & 0x1F) * 527) + 23) >> 6;
                  DATA.SELECT_COLOR_SAVE[0]                 = y;
                  DATA.SELECT_COLOR_SAVE[1]                 = x;
                  DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR]  = 0;
                  DATA.SELECT_COLOR                         = 0;
                  DATA.IS_SELECT_COLOR                      = true;
                  DATA.MATRIX_TIME                          = millis();
                }
              }
        if(BUTTON_INVERSION.IS_PRESS(X, Y))
        {
          for(uint8_t y = 0; y <= 4; ++y)
            for(uint8_t x = 0; x <= 2; ++x)
              SAVE.COLOR[y][x] = 0xffff - SAVE.COLOR[y][x];
          GFX->fillScreen(SAVE.COLOR[4][1]);
          MAIN_MENU();   
          EEPROM_SAVE();   
        }

      }
       else
      {
        uint8_t BATTON_NAME[13]  = {1, 2, 3, 98, 4, 5, 6, 0, 7, 8, 9, 99, 99};
        uint8_t BATTON_NAMBER   = 0;
        if (millis() - DATA.MATRIX_TIME >= 400)
          for(uint8_t y = 0; y <= 2; ++y)
            for(uint8_t x = 0; x <= 3; ++x)
            {
              if (X >= 20 + x * 180 && X <= 170 + x * 180 && Y >= 230 + y * 85 && Y <= 300 + y * 85)
              {
                if (BATTON_NAME[BATTON_NAMBER] < 10)
                {   
                    if (DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 0)
                      DATA.COLOR[DATA.SELECT_COLOR] = BATTON_NAME[BATTON_NAMBER];
                    if (DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 1 || DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 2)
                      DATA.COLOR[DATA.SELECT_COLOR] = DATA.COLOR[DATA.SELECT_COLOR] * 10 + BATTON_NAME[BATTON_NAMBER];
                    if (DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] != 2)
                    {
                      ++DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR];
                    }
                    else
                    {
                      DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR]  = 0;
                      if (DATA.SELECT_COLOR != 2)
                      {
                        ++DATA.SELECT_COLOR;
                      }
                      else
                        DATA.SELECT_COLOR                       = 0;
                    }
                }
                else if (BATTON_NAME[BATTON_NAMBER] == 98)
                { 

                  if (DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 1 || DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 2)
                    DATA.COLOR[DATA.SELECT_COLOR] = (int)(DATA.COLOR[DATA.SELECT_COLOR] / 10);
                  if (DATA.SELECT_COLOR == 0 && DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 0 && DATA.COLOR[0] != 0 && DATA.COLOR[1] != 0 && DATA.COLOR[2] != 0)
                  {
                    DATA.SELECT_COLOR                         = 2;
                    DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR]  = 3;
                    DATA.COLOR[DATA.SELECT_COLOR] = (int)(DATA.COLOR[DATA.SELECT_COLOR] / 10);
                  }
                  if (DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 0)
                    DATA.COLOR[DATA.SELECT_COLOR]             = 0;
                  if (DATA.SELECT_COLOR != 0 && DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] == 0)
                  {
                    --DATA.SELECT_COLOR;
                    DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR]  = 3;
                    DATA.COLOR[DATA.SELECT_COLOR] = (int)(DATA.COLOR[DATA.SELECT_COLOR] / 10);
                  }
                  if (DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR] != 0)
                    --DATA.COUNT_COLOR_DOWN[DATA.SELECT_COLOR];
                }
                else if (BATTON_NAME[BATTON_NAMBER] == 99)
                {
                  SAVE.COLOR[DATA.SELECT_COLOR_SAVE[0]][DATA.SELECT_COLOR_SAVE[1]] = TO.RGB_TO_RGB16(DATA.COLOR[0], DATA.COLOR[1], DATA.COLOR[2]);
                  GFX->fillScreen(SAVE.COLOR[4][1]);
                  MAIN_MENU();
                  EEPROM_SAVE();
                  DATA.IS_SELECT_COLOR            = false;
                }
                DATA.MATRIX_TIME  = millis();
              }
              ++BATTON_NAMBER;
            }
      }
    }
    else  if (DATA.MENU == 5)
    { 
      if (DATA.IS_CARD)
      {
        if (BUTTON_CH_ACTIVE[0].IS_PRESS(X, Y))
        {
          SAVE.IS_ACTIVE[0] = !SAVE.IS_ACTIVE[0];
          EEPROM_SAVE();
        }
        if (BUTTON_CH_ACTIVE[1].IS_PRESS(X, Y))
        {
          SAVE.IS_ACTIVE[1] = !SAVE.IS_ACTIVE[1];
          EEPROM_SAVE();
        }
        if (BUTTON_CH_ACTIVE[2].IS_PRESS(X, Y))
        {
          SAVE.IS_ACTIVE[2] = !SAVE.IS_ACTIVE[2];
          EEPROM_SAVE();
        }
      }
      if (BUTTON_WIFI.IS_PRESS(X, Y))
      {
        SAVE.IS_WIFI = !SAVE.IS_WIFI;
        EEPROM_SAVE();
        delay(500);
        ESP.restart();
      }
        
      if (millis() - DATA.MATRIX_TIME >= 400)
        for(uint8_t y = 0; y <= 2; ++y)
          for(uint8_t x = 0; x <= 4; ++x)
            if (X >= 100 + x * 70 && X <= 146 + x * 70 && Y >= 160 + y * 55 && Y <= 206 + y * 55)
            {
              SAVE.CURRENT_HOUR[y][x] = 0;
              SAVE.WATT_HOUR[y][x]    = 0;
              DATA.MATRIX_TIME        = millis();
              EEPROM_SAVE();
            }
        if(BUTTON_CLEAR_DIRECTORY.IS_PRESS(X, Y) && TO.IS_CLEAR_DIRECTORY && DATA.IS_CARD)
        {
          TO.IS_CLEAR_DIRECTORY = false;
          TO.CLEAR_DIRECTORY(SD);
        }
        if(BUTTON_WIPE_DATA.IS_PRESS(X, Y))
        {
          EEPROM_CLEAR();
          delay(500);
          ESP.restart();
        }
    }

    if (MENU[0].IS_PRESS(X, Y))
    {
      DATA.MENU       = 0;
      DATA.CLICK_ONE  = true;
    } 
    else if (MENU[1].IS_PRESS(X, Y))
    {
      DATA.CHANNEL    = 0;
      DATA.MENU       = 1;
      DATA.CLICK_ONE  = true;
    }
    else if (MENU[2].IS_PRESS(X, Y))
    {
      DATA.CHANNEL    = 1;
      DATA.MENU       = 2;
      DATA.CLICK_ONE  = true;
    }
    else if (MENU[3].IS_PRESS(X, Y))
    {
      DATA.CHANNEL    = 2;
      DATA.MENU       = 3;
      DATA.CLICK_ONE  = true;
    }
    else if (MENU[4].IS_PRESS(X, Y))
    {
      DATA.MENU       = 4;
      DATA.CLICK_ONE  = true;
    }
    else if (MENU[5].IS_PRESS(X, Y))
    {
      DATA.MENU       = 5;
      DATA.CLICK_ONE  = true;
    }
  }
  
  DATA.VOLTAGES[0][DATA.NUMBER]                 = INA226_CH1.getBusVoltage_V();
  DATA.CURRENTS[0][DATA.NUMBER]                 = INA226_CH1.getCurrent_A();
  DATA.WATT[0][DATA.NUMBER]                     = DATA.CURRENTS[0][DATA.NUMBER] * DATA.VOLTAGES[0][DATA.NUMBER];
  DATA.TIME[0]                                  = (millis() - SAVE.SET_MILLISECOND[0][SAVE.ACTIV_NAMBER[0]]);
  SAVE.CURRENT_HOUR[0][SAVE.ACTIV_NAMBER[0]]    += DATA.CURRENTS[0][DATA.NUMBER] * DATA.TIME[0] / 3600000;             //Расчет емкости  в мАч
  SAVE.WATT_HOUR[0][SAVE.ACTIV_NAMBER[0]]       += DATA.WATT[0][DATA.NUMBER] * DATA.TIME[0] / 3600000;  //Расчет мВтч
  SAVE.SET_MILLISECOND[0][SAVE.ACTIV_NAMBER[0]] = millis();
  if (SAVE.IS_LIMIT)
  {
    if (DATA.VOLTAGES[0][DATA.NUMBER] <= SAVE.LIMIT[0])
    {
      digitalWrite(CONFIG.PIN_ANALOG_READ, HIGH);
    }
    else if (DATA.VOLTAGES[0][DATA.NUMBER] >= SAVE.LIMIT[1])
    {
      digitalWrite(CONFIG.PIN_ANALOG_READ, LOW);
    }
  }
  else
    digitalWrite(CONFIG.PIN_ANALOG_READ, LOW);
  
  
  DATA.VOLTAGES[1][DATA.NUMBER]                 = INA226_CH2.getBusVoltage_V();
  DATA.CURRENTS[1][DATA.NUMBER]                 = INA226_CH2.getCurrent_A();
  DATA.WATT[1][DATA.NUMBER]                     = DATA.CURRENTS[1][DATA.NUMBER] * DATA.VOLTAGES[1][DATA.NUMBER];
  DATA.TIME[1]                                  = (millis() - SAVE.SET_MILLISECOND[1][SAVE.ACTIV_NAMBER[1]]);
  SAVE.CURRENT_HOUR[1][SAVE.ACTIV_NAMBER[1]]    += DATA.CURRENTS[1][DATA.NUMBER] * DATA.TIME[1] / 3600000;             //Расчет емкости  в мАч
  SAVE.WATT_HOUR[1][SAVE.ACTIV_NAMBER[1]]       += DATA.WATT[1][DATA.NUMBER] * DATA.TIME[1] / 3600000;  //Расчет мВтч
  SAVE.SET_MILLISECOND[1][SAVE.ACTIV_NAMBER[1]] = millis();

  DATA.VOLTAGES[2][DATA.NUMBER]                 = INA226_CH3.getBusVoltage_V();
  DATA.CURRENTS[2][DATA.NUMBER]                 = INA226_CH3.getCurrent_A();
  DATA.WATT[2][DATA.NUMBER]                     = DATA.CURRENTS[2][DATA.NUMBER] * DATA.VOLTAGES[2][DATA.NUMBER];
  DATA.TIME[2]                                  = (millis() - SAVE.SET_MILLISECOND[2][SAVE.ACTIV_NAMBER[2]]);
  SAVE.CURRENT_HOUR[2][SAVE.ACTIV_NAMBER[2]]    += DATA.CURRENTS[2][DATA.NUMBER] * DATA.TIME[2] / 3600000;             //Расчет емкости  в мАч
  SAVE.WATT_HOUR[2][SAVE.ACTIV_NAMBER[2]]       += DATA.WATT[2][DATA.NUMBER] * DATA.TIME[2] / 3600000;  //Расчет мВтч
  SAVE.SET_MILLISECOND[2][SAVE.ACTIV_NAMBER[2]] = millis();                                                                                    //Обновляем текущее время

  if (SAVE.IS_ACTIVE[0] || SAVE.IS_ACTIVE[1] || SAVE.IS_ACTIVE[2])
  {
    char DATE[14] = "DD_MM_YYYY_hh";
    RTC.now().toString(DATE);
    char TIME[20] = "DD.MM.YYYY hh:mm:ss";
    RTC.now().toString(TIME);
    String MESSAGE = TIME; 
    if (SAVE.IS_ACTIVE[0])
    {
      MESSAGE += ";CH1;" + String(DATA.VOLTAGES[0][DATA.NUMBER]);
      MESSAGE += ";" + String(DATA.CURRENTS[0][DATA.NUMBER], 3); 
      MESSAGE += ";" + String(DATA.WATT[0][DATA.NUMBER], 3); 
      MESSAGE += ";" + String(SAVE.CURRENT_HOUR[0][SAVE.ACTIV_NAMBER[0]], 3); 
      MESSAGE += ";" + String(SAVE.WATT_HOUR[0][SAVE.ACTIV_NAMBER[0]], 3);  
    }
    if (SAVE.IS_ACTIVE[1])
    {
      MESSAGE += ";CH2;" + String(DATA.VOLTAGES[1][DATA.NUMBER]);
      MESSAGE += ";" + String(DATA.CURRENTS[1][DATA.NUMBER], 3); 
      MESSAGE += ";" + String(DATA.WATT[1][DATA.NUMBER], 3); 
      MESSAGE += ";" + String(SAVE.CURRENT_HOUR[1][SAVE.ACTIV_NAMBER[1]], 3); 
      MESSAGE += ";" + String(SAVE.WATT_HOUR[1][SAVE.ACTIV_NAMBER[1]], 3);   
    } 
    if (SAVE.IS_ACTIVE[2])
    {
      MESSAGE += ";CH3;" + String(DATA.VOLTAGES[2][DATA.NUMBER]);
      MESSAGE += ";" + String(DATA.CURRENTS[2][DATA.NUMBER], 3);  
      MESSAGE += ";" + String(DATA.WATT[2][DATA.NUMBER], 3);  
      MESSAGE += ";" + String(SAVE.CURRENT_HOUR[2][SAVE.ACTIV_NAMBER[2]], 3);  
      MESSAGE += ";" + String(SAVE.WATT_HOUR[2][SAVE.ACTIV_NAMBER[2]], 3);  
    } 
    char NAME[19] = "/";
    strcat(NAME, DATE);
    strcat(NAME, ".csv");
    File file = SD.open(NAME, FILE_APPEND);
    if (file)
      file.print(MESSAGE + "\n");
    file.close();
  }
      
  
  ++DATA.NUMBER;
  if (DATA.NUMBER > 660)
  {
    --DATA.NUMBER;
    for (uint16_t  i = 0; i <= 659; ++i)
    { 

        DATA.VOLTAGES[0][i] = DATA.VOLTAGES[0][i + 1];
        DATA.CURRENTS[0][i] = DATA.CURRENTS[0][i + 1];
        DATA.WATT[0][i]     = DATA.WATT[0][i + 1];

        DATA.VOLTAGES[1][i] = DATA.VOLTAGES[1][i + 1];
        DATA.CURRENTS[1][i] = DATA.CURRENTS[1][i + 1];
        DATA.WATT[1][i]     = DATA.WATT[1][i + 1];

        DATA.VOLTAGES[2][i] = DATA.VOLTAGES[2][i + 1];
        DATA.CURRENTS[2][i] = DATA.CURRENTS[2][i + 1];
        DATA.WATT[2][i]     = DATA.WATT[2][i + 1];
    }
  }

  if (DATA.CLICK_ONE)
    MAIN_MENU();

  if (DATA.MENU == 0)
  {
    MAIN();
  }
  else if (DATA.MENU == 1 || DATA.MENU == 2 || DATA.MENU == 3)
  {
    CHART();
  }
  else if (DATA.MENU == 4)
  {
    PALETTES();
  }
  else if (DATA.MENU == 5)
  {
    SETTINGS();
  }
  CANVAS->flush();
}
