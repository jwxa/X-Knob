#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl.h"
#endif
#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_SRC_DOT_BLUE
#define LV_ATTRIBUTE_IMG_IMG_SRC_DOT_BLUE
#endif
const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IMG_SRC_DOT_BLUE uint8_t img_src_dot_blue_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x62, 0x6f, 0xb8, 0x6f, 0xed, 0x6f, 0xff, 0x6f, 0xed, 0x6f, 0xb8, 0x6f, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6f, 0x30, 0x6f, 0xc9, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xc9, 0x6f, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x6f, 0x30, 0x6f, 0xed, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xed, 0x6f, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x6f, 0xc9, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xc9, 0x00, 0x00, 
  0x6f, 0x62, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x62, 
  0x6f, 0xb8, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xb8, 
  0x6f, 0xed, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xed, 
  0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 
  0x6f, 0xed, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xed, 
  0x6f, 0xb8, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xb8, 
  0x6f, 0x62, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x62, 
  0x00, 0x00, 0x6f, 0xc9, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xc9, 0x00, 0x00, 
  0x00, 0x00, 0x6f, 0x30, 0x6f, 0xed, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xed, 0x6f, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6f, 0x30, 0x6f, 0xc9, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xc9, 0x6f, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x62, 0x6f, 0xb8, 0x6f, 0xed, 0x6f, 0xff, 0x6f, 0xed, 0x6f, 0xb8, 0x6f, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x53, 0x62, 0x39, 0x53, 0xb8, 0x39, 0x53, 0xed, 0x39, 0x53, 0xff, 0x39, 0x53, 0xed, 0x39, 0x53, 0xb8, 0x39, 0x53, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x53, 0x30, 0x39, 0x53, 0xc9, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xc9, 0x39, 0x53, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x39, 0x53, 0x30, 0x39, 0x53, 0xed, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xed, 0x39, 0x53, 0x30, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x39, 0x53, 0xc9, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xc9, 0x00, 0x00, 0x00, 
  0x39, 0x53, 0x62, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0x62, 
  0x39, 0x53, 0xb8, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xb8, 
  0x39, 0x53, 0xed, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xed, 
  0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 
  0x39, 0x53, 0xed, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xed, 
  0x39, 0x53, 0xb8, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xb8, 
  0x39, 0x53, 0x62, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0x62, 
  0x00, 0x00, 0x00, 0x39, 0x53, 0xc9, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xc9, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x39, 0x53, 0x30, 0x39, 0x53, 0xed, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xed, 0x39, 0x53, 0x30, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x53, 0x30, 0x39, 0x53, 0xc9, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xff, 0x39, 0x53, 0xc9, 0x39, 0x53, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x53, 0x62, 0x39, 0x53, 0xb8, 0x39, 0x53, 0xed, 0x39, 0x53, 0xff, 0x39, 0x53, 0xed, 0x39, 0x53, 0xb8, 0x39, 0x53, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x39, 0x62, 0x53, 0x39, 0xb8, 0x53, 0x39, 0xed, 0x53, 0x39, 0xff, 0x53, 0x39, 0xed, 0x53, 0x39, 0xb8, 0x53, 0x39, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x39, 0x30, 0x53, 0x39, 0xc9, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xc9, 0x53, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x53, 0x39, 0x30, 0x53, 0x39, 0xed, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xed, 0x53, 0x39, 0x30, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x53, 0x39, 0xc9, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xc9, 0x00, 0x00, 0x00, 
  0x53, 0x39, 0x62, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0x62, 
  0x53, 0x39, 0xb8, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xb8, 
  0x53, 0x39, 0xed, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xed, 
  0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 
  0x53, 0x39, 0xed, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xed, 
  0x53, 0x39, 0xb8, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xb8, 
  0x53, 0x39, 0x62, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0x62, 
  0x00, 0x00, 0x00, 0x53, 0x39, 0xc9, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xc9, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x53, 0x39, 0x30, 0x53, 0x39, 0xed, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xed, 0x53, 0x39, 0x30, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x39, 0x30, 0x53, 0x39, 0xc9, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xff, 0x53, 0x39, 0xc9, 0x53, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x39, 0x62, 0x53, 0x39, 0xb8, 0x53, 0x39, 0xed, 0x53, 0x39, 0xff, 0x53, 0x39, 0xed, 0x53, 0x39, 0xb8, 0x53, 0x39, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x63, 0x51, 0x62, 0xc8, 0x64, 0x50, 0xb8, 0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xb8, 0xc8, 0x63, 0x51, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xca, 0x65, 0x50, 0x30, 0xc8, 0x64, 0x50, 0xc9, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xc9, 0xca, 0x65, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xca, 0x65, 0x50, 0x30, 0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xed, 0xca, 0x65, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xc8, 0x64, 0x50, 0xc9, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xc9, 0x00, 0x00, 0x00, 0x00, 
  0xc8, 0x63, 0x51, 0x62, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x63, 0x51, 0x62, 
  0xc8, 0x64, 0x50, 0xb8, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xb8, 
  0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xed, 
  0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 
  0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xed, 
  0xc8, 0x64, 0x50, 0xb8, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xb8, 
  0xc8, 0x63, 0x51, 0x62, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x63, 0x51, 0x62, 
  0x00, 0x00, 0x00, 0x00, 0xc8, 0x64, 0x50, 0xc9, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xc9, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xca, 0x65, 0x50, 0x30, 0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xed, 0xca, 0x65, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xca, 0x65, 0x50, 0x30, 0xc8, 0x64, 0x50, 0xc9, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xc9, 0xca, 0x65, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x63, 0x51, 0x62, 0xc8, 0x64, 0x50, 0xb8, 0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xff, 0xc8, 0x64, 0x50, 0xed, 0xc8, 0x64, 0x50, 0xb8, 0xc8, 0x63, 0x51, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t img_src_dot_blue = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 15,
  .header.h = 15,
  .data_size = 225 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = img_src_dot_blue_map,
};