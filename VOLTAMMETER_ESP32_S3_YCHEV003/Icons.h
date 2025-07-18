#pragma once
#include <Arduino.h>

// 'PALETTE, 80x80px
const unsigned char PALETTE_ICON[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xf0, 0x1f, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xf0, 0x1e, 0x0f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x1e, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 
  0x78, 0x1c, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3c, 0x3c, 0x07, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xc0, 0x7f, 0xfe, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x7f, 0xff, 
  0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0x10, 0x00, 0x00, 0x00, 
  0x06, 0x7f, 0xff, 0xff, 0xff, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x08, 0x3f, 0xff, 0xff, 0xff, 0xc0, 
  0xf0, 0x00, 0x00, 0x00, 0x10, 0x1f, 0xff, 0xff, 0xff, 0x83, 0xe0, 0x00, 0x00, 0x00, 0x10, 0x1f, 
  0xff, 0xff, 0xff, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x10, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 0xc0, 0x00, 
  0x00, 0x00, 0x38, 0x1e, 0x1f, 0xff, 0xf8, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x38, 0x38, 0x07, 0xff, 
  0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x03, 0xff, 0xc1, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x3f, 0xf0, 0x03, 0xff, 0x83, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x01, 0xff, 0x07, 0xfc, 
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x01, 0xfe, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 
  0x01, 0xfc, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x01, 0xf8, 0x7f, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0x01, 0xf0, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x03, 0xe1, 
  0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x07, 0xc3, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3c, 0x0f, 0x87, 0xff, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x0f, 0xff, 0x0c, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x1f, 0xfe, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
  0xfc, 0x3f, 0xfc, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0x7f, 0xf8, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xf8, 0x1f, 0xf0, 0x78, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x0f, 
  0xe0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x81, 0x07, 0xc1, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0xfe, 0x00, 0xc3, 0x83, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x21, 0x07, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x20, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 
  0x7e, 0x10, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0xff, 0x00, 0x7f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xe1, 0xff, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe3, 0xff, 0x81, 
  0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc3, 0xff, 0x87, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0xc3, 0xff, 0x8f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc7, 0xff, 0x8f, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x87, 0xff, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 
  0xff, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x14, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



// 'HOME, 80x80px
const unsigned char HOME_ICON [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3f, 0xfe, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x7f, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0xff, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x3f, 
  0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xf0, 0x07, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0xc3, 0xff, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x83, 0xe0, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x07, 0xf0, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x1f, 0xf8, 0x3f, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xf8, 0x3f, 0xfe, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x7f, 0xff, 
  0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe1, 0xff, 0xff, 0x83, 0xfc, 0x00, 0x00, 0x00, 0x00, 
  0x7f, 0xc3, 0xff, 0xff, 0xe1, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0xff, 0xff, 0xf0, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0xff, 0xff, 0xf8, 0x3f, 0x80, 0x00, 0x00, 0x00, 0xfc, 0x3f, 
  0xff, 0xff, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 
  0x00, 0x00, 0x20, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 
  0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 
  0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 
  0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 
  0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 
  0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x01, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xc0, 0x01, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'SETTINGS, 80x80px
const unsigned char SETTING_ICON [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x7f, 0xfc, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xc0, 0xff, 0xff, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x0f, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xff, 0xc0, 0x03, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x01, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x01, 
  0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 
  0xe0, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xfe, 
  0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 
  0x7f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x0f, 
  0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 
  0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
  0x80, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0x03, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xff, 0xf0, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 
  0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0xff, 0xfe, 0x07, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x7f, 0xfc, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'WIFI', 30x30px
const unsigned char WIFI_ICON [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 
  0x00, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xc0, 0x1f, 0xe0, 0x1f, 0xe0, 
  0x7f, 0x80, 0x03, 0xf8, 0x7e, 0x00, 0x01, 0xfc, 0xf8, 0x01, 0x00, 0x7c, 0xf0, 0x3f, 0xf0, 0x3c, 
  0x60, 0xff, 0xfc, 0x18, 0x01, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x00, 0x07, 0xe0, 0x1f, 0x80, 
  0x07, 0xc0, 0x0f, 0x80, 0x07, 0x80, 0x07, 0x80, 0x03, 0x07, 0x83, 0x00, 0x00, 0x0f, 0xc0, 0x00, 
  0x00, 0x1f, 0xe0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 
  0x00, 0x1f, 0xe0, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'FAN, 80x80px
const unsigned char FAN_ICON [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xef, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xf0, 
  0x07, 0x83, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0xf0, 0x07, 0x03, 0xff, 0xf0, 0x00, 0x00, 
  0x07, 0xff, 0xe0, 0x78, 0x07, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xe0, 0x78, 0x07, 0x01, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x78, 0x07, 0x83, 0xfc, 0x00, 0x0f, 0xf0, 0x00, 0x1f, 
  0xe0, 0x78, 0x07, 0x87, 0xf8, 0x00, 0xff, 0xf8, 0x00, 0x0f, 0xf0, 0xf8, 0x07, 0xff, 0xf0, 0x00, 
  0xff, 0xfc, 0x00, 0x03, 0xff, 0xf8, 0x07, 0xff, 0xe0, 0x00, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xf8, 
  0x07, 0xff, 0xc0, 0x00, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xf8, 0x07, 0xff, 0x80, 0x00, 0x7f, 0xff, 
  0x00, 0x00, 0x7f, 0xf8, 0x07, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x3f, 0xf8, 0x07, 0xfe, 
  0x00, 0x00, 0x1f, 0xff, 0x00, 0x30, 0x3f, 0xf8, 0x07, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x78, 
  0x1f, 0xf8, 0x07, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x7c, 0x0f, 0xf8, 0x07, 0xf8, 0x0f, 0x00, 
  0x07, 0xff, 0x00, 0x7c, 0x07, 0xf8, 0x07, 0xf0, 0x3f, 0xc0, 0x07, 0xff, 0x00, 0xfe, 0x07, 0xf8, 
  0x07, 0xe0, 0x7f, 0xf0, 0x07, 0xff, 0x00, 0xff, 0x03, 0xf8, 0x07, 0xe0, 0x7f, 0xf8, 0x03, 0xfe, 
  0x01, 0xff, 0x03, 0xf8, 0x07, 0xc0, 0xff, 0xfe, 0x03, 0xfe, 0x01, 0xff, 0x81, 0xf8, 0x07, 0xc0, 
  0xff, 0xff, 0x03, 0xfe, 0x03, 0xff, 0xc1, 0xf8, 0x07, 0xc1, 0xff, 0xff, 0x83, 0xfe, 0x07, 0xff, 
  0xc1, 0xf8, 0x07, 0x81, 0xff, 0xff, 0xc1, 0xfc, 0x07, 0xff, 0xc0, 0xf8, 0x07, 0x83, 0xff, 0xff, 
  0xe0, 0x0c, 0x0f, 0xff, 0xc0, 0xf8, 0x07, 0x83, 0xff, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xc0, 0xf8, 
  0x07, 0x83, 0xff, 0xff, 0xc7, 0xf8, 0x7f, 0xff, 0xc0, 0x78, 0x07, 0x07, 0xff, 0xff, 0x9f, 0xfc, 
  0x7f, 0xff, 0x80, 0x78, 0x07, 0x07, 0xff, 0xff, 0x3f, 0xfe, 0x7f, 0xff, 0x00, 0x78, 0x07, 0x03, 
  0x00, 0x1e, 0x7f, 0xff, 0x3f, 0xfe, 0x00, 0x78, 0x07, 0x00, 0x00, 0x02, 0x7f, 0xff, 0x3f, 0xf8, 
  0x00, 0x78, 0x07, 0x00, 0x00, 0x00, 0xff, 0xff, 0x9f, 0xe0, 0x00, 0x78, 0x07, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x9f, 0x80, 0x00, 0x38, 0x07, 0x00, 0x00, 0x00, 0xff, 0xff, 0x9c, 0x00, 0x00, 0x38, 
  0x07, 0x00, 0x00, 0x0c, 0xff, 0xff, 0x80, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x7c, 0xff, 0xff, 
  0x80, 0x00, 0x00, 0x38, 0x07, 0x00, 0x03, 0xfe, 0xff, 0xff, 0x80, 0x00, 0x00, 0x78, 0x07, 0x00, 
  0x0f, 0xfe, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x78, 0x07, 0x00, 0x1f, 0xfe, 0x7f, 0xff, 0x38, 0x00, 
  0x00, 0x78, 0x07, 0x00, 0x7f, 0xff, 0x3f, 0xfe, 0x7f, 0xff, 0xf0, 0x78, 0x07, 0x00, 0xff, 0xff, 
  0x9f, 0xfc, 0x7f, 0xff, 0xf0, 0x78, 0x07, 0x80, 0xff, 0xff, 0x0f, 0xf8, 0xff, 0xff, 0xf0, 0x78, 
  0x07, 0x81, 0xff, 0xfe, 0x01, 0xc3, 0xff, 0xff, 0xe0, 0xf8, 0x07, 0x81, 0xff, 0xfc, 0x10, 0x03, 
  0xff, 0xff, 0xe0, 0xf8, 0x07, 0x81, 0xff, 0xf8, 0x1f, 0xe1, 0xff, 0xff, 0xe0, 0xf8, 0x07, 0xc1, 
  0xff, 0xf0, 0x1f, 0xe0, 0xff, 0xff, 0xc0, 0xf8, 0x07, 0xc0, 0xff, 0xe0, 0x3f, 0xe0, 0x7f, 0xff, 
  0xc1, 0xf8, 0x07, 0xc0, 0xff, 0xe0, 0x3f, 0xe0, 0x3f, 0xff, 0x81, 0xf8, 0x07, 0xe0, 0x7f, 0xc0, 
  0x3f, 0xf0, 0x0f, 0xff, 0x83, 0xf8, 0x07, 0xe0, 0x7f, 0xc0, 0x3f, 0xf0, 0x07, 0xff, 0x03, 0xf8, 
  0x07, 0xf0, 0x3f, 0x80, 0x3f, 0xf0, 0x01, 0xfe, 0x07, 0xf8, 0x07, 0xf8, 0x1f, 0x80, 0x3f, 0xf8, 
  0x00, 0x7c, 0x07, 0xf8, 0x07, 0xf8, 0x1f, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x0f, 0xf8, 0x07, 0xfc, 
  0x0f, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x1f, 0xf8, 0x07, 0xfe, 0x07, 0x00, 0x3f, 0xfc, 0x00, 0x00, 
  0x1f, 0xf8, 0x07, 0xff, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xf8, 0x07, 0xff, 0x80, 0x00, 
  0x3f, 0xff, 0x00, 0x00, 0x7f, 0xf8, 0x07, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0x80, 0x00, 0xff, 0xf8, 
  0x07, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xc0, 0x01, 0xff, 0xf8, 0x07, 0xff, 0xf0, 0x00, 0x1f, 0xff, 
  0xc0, 0x03, 0xff, 0xf8, 0x07, 0x87, 0xf8, 0x00, 0x0f, 0xff, 0x80, 0x07, 0xf0, 0xf8, 0x07, 0x83, 
  0xfc, 0x00, 0x07, 0xfc, 0x00, 0x1f, 0xe0, 0x78, 0x07, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 
  0xe0, 0x78, 0x07, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x78, 0x07, 0x01, 0xff, 0xe0, 
  0x00, 0x00, 0x03, 0xff, 0xe0, 0x78, 0x07, 0x83, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0xf0, 
  0x07, 0xcf, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xf9, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//'FAN_MIN, 30x30px
const unsigned char FAN_MIN_ICON [] PROGMEM = {
  0x7f, 0xff, 0xff, 0xf8, 0xff, 0xf8, 0x7f, 0xf8, 0x8f, 0x80, 0x07, 0xcc, 0x8e, 0x07, 0x03, 0xcc, 
  0xfc, 0x1f, 0x80, 0xfc, 0xf8, 0x0f, 0xc0, 0x7c, 0xf0, 0x07, 0xc2, 0x3c, 0xe0, 0x07, 0xc7, 0x3c, 
  0xe7, 0x87, 0xc7, 0x1c, 0xc7, 0xe3, 0xc7, 0x9c, 0xcf, 0xf3, 0x8f, 0x8c, 0xcf, 0xf0, 0x1f, 0x8c, 
  0x8f, 0xef, 0xbf, 0x8c, 0x80, 0x0f, 0xde, 0x0c, 0x80, 0x1f, 0xd8, 0x0c, 0x80, 0xdf, 0xc0, 0x0c, 
  0x83, 0xef, 0xc0, 0x0c, 0x87, 0xef, 0xbf, 0xcc, 0xcf, 0xe2, 0x7f, 0xcc, 0xcf, 0xce, 0x3f, 0xcc, 
  0xc7, 0x8f, 0x1f, 0x9c, 0xe7, 0x8f, 0x0f, 0x1c, 0xe3, 0x0f, 0x80, 0x3c, 0xf1, 0x0f, 0x80, 0x3c, 
  0xf8, 0x0f, 0xc0, 0x7c, 0xfc, 0x0f, 0xe0, 0xfc, 0x8e, 0x03, 0x83, 0xcc, 0x8f, 0x80, 0x07, 0xcc, 
  0xdf, 0xf8, 0x7f, 0xf8, 0x7f, 0xff, 0xff, 0xf8
};

// 'FAN_MIN_2, 30x30px
const unsigned char FAN_MIN_2_ICON [] PROGMEM = {
  0x7f, 0xff, 0xff, 0xf8, 0xff, 0xf8, 0x7f, 0xfc, 0x8f, 0x80, 0x07, 0xcc, 0x8e, 0x07, 0x03, 0xcc, 
  0xfc, 0x1f, 0x80, 0xfc, 0xf8, 0x2f, 0xd0, 0x7c, 0xf0, 0x67, 0xda, 0x3c, 0xe0, 0x17, 0xc3, 0x3c, 
  0xe7, 0x87, 0xd7, 0x1c, 0xc7, 0xe3, 0xc7, 0x9c, 0xcf, 0xf3, 0x8f, 0x8c, 0xcf, 0xf0, 0x1f, 0x8c, 
  0x8f, 0xe7, 0xbf, 0x8c, 0x80, 0x0f, 0xde, 0x0c, 0x8a, 0x1f, 0xd8, 0x84, 0x8c, 0x5f, 0xc2, 0xc4, 
  0x83, 0xef, 0xc0, 0x0c, 0x87, 0xef, 0xbf, 0xcc, 0xcf, 0xe2, 0x7f, 0xcc, 0xcf, 0xce, 0x7f, 0xcc, 
  0xc7, 0x8f, 0x1f, 0x8c, 0xe7, 0x8f, 0x0f, 0x1c, 0xe3, 0x2f, 0xa2, 0x3c, 0xf1, 0x6f, 0x98, 0x3c, 
  0xf8, 0x2f, 0xd0, 0x7c, 0xfc, 0x0f, 0xe0, 0xfc, 0xce, 0x07, 0x83, 0xcc, 0x8f, 0x80, 0x07, 0xcc, 
  0xdf, 0xf0, 0x7f, 0xfc, 0x7f, 0xff, 0xff, 0xf8
};

// 'POINT, 20x20px
const unsigned char POINT_ICON [] PROGMEM = {
  0x03, 0xfc, 0x00, 0x0f, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x3f, 0xff, 0xc0, 0x7f, 0xff, 0xe0, 0x7f, 
  0xff, 0xe0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0xff, 0xff, 
  0xf0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xe0, 0x7f, 0xff, 0xe0, 0x3f, 0xff, 0xc0, 
  0x3f, 0xff, 0xc0, 0x1f, 0xff, 0x00, 0x07, 0xfe, 0x00, 0x01, 0xf8, 0x00
};
