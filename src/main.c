// Scope Chip v1.0.7
// by David Lloyd, March 2023.

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <wchar.h>

const uint8_t font8x8[128][8] = {
  0x00, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C,  // 00   0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,  // 01   1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18,  // 02   2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18,  // 03   3
  0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18,  // 04   4
  0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18,  // 05   5
  0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  // 06   6
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 07   7
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 08   8
  0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  // 09   9
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0A  10
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  // 0B  11
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0C  12
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0D  13
  0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18,  // 0E  14
  0x00, 0x00, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x18,  // 0F  15
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 10  16
  0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00,  // 11  17
  0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00,  // 12  18
  0x18, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00,  // 13  19
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x18, 0x18, 0x18,  // 14  20
  0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18,  // 15  21
  0x18, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x18,  // 16  22
  0xC3, 0xC3, 0x66, 0x3C, 0x3C, 0x66, 0xC3, 0xC3,  // 17  23
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,  // 18  24
  0x00, 0x10, 0x20, 0x7C, 0x20, 0x10, 0x00, 0x00,  // 19  25
  0x00, 0x10, 0x08, 0x7C, 0x08, 0x10, 0x00, 0x00,  // 1A  26
  0x00, 0x10, 0x10, 0x10, 0x54, 0x38, 0x10, 0x00,  // 1B  27
  0x00, 0x10, 0x38, 0x54, 0x10, 0x10, 0x10, 0x00,  // 1C  28
  0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18,  // 1D  29
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 1E  30
  0x00, 0x1C, 0x0C, 0x14, 0x20, 0x40, 0x00, 0x00,  // 1F  31
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 20  32
  0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00,  // 21  33 !
  0x00, 0x28, 0x28, 0x28, 0x00, 0x00, 0x00, 0x00,  // 22  34 "
  0x00, 0x28, 0x7C, 0x28, 0x28, 0x7C, 0x28, 0x00,  // 23  35 #
  0x00, 0x38, 0x54, 0x30, 0x18, 0x54, 0x38, 0x00,  // 24  36 $
  0x00, 0x44, 0x4C, 0x18, 0x30, 0x64, 0x44, 0x00,  // 25  37 %
  0x00, 0x20, 0x50, 0x20, 0x54, 0x48, 0x34, 0x00,  // 26  38 &
  0x00, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00,  // 27  39 '
  0x00, 0x10, 0x20, 0x20, 0x20, 0x20, 0x10, 0x00,  // 28  40 (
  0x00, 0x20, 0x10, 0x10, 0x10, 0x10, 0x20, 0x00,  // 29  41 )
  0x00, 0x44, 0x28, 0x7C, 0x28, 0x44, 0x00, 0x00,  // 2A  42 *
  0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x00,  // 2B  43 +
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x20,  // 2C  44 ,
  0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00,  // 2D  45 -
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00,  // 2E  46 .
  0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00,  // 2F  47 /
  0x00, 0x38, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00,  // 30  48 0
  0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00,  // 31  49 1
  0x00, 0x38, 0x44, 0x08, 0x10, 0x20, 0x7C, 0x00,  // 32  50 2
  0x00, 0x38, 0x44, 0x18, 0x04, 0x44, 0x38, 0x00,  // 33  51 3
  0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x00,  // 34  52 4
  0x00, 0x78, 0x40, 0x78, 0x04, 0x44, 0x38, 0x00,  // 35  53 5
  0x00, 0x38, 0x40, 0x78, 0x44, 0x44, 0x38, 0x00,  // 36  54 6
  0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x20, 0x00,  // 37  55 7
  0x00, 0x38, 0x44, 0x38, 0x44, 0x44, 0x38, 0x00,  // 38  56 8
  0x00, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x78, 0x00,  // 39  57 9
  0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00,  // 3A  58 :
  0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x10, 0x20,  // 3B  59 ;
  0x00, 0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00,  // 3C  60 <
  0x00, 0x00, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x00,  // 3D  61 =
  0x00, 0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00,  // 3E  62 >
  0x00, 0x38, 0x44, 0x08, 0x10, 0x00, 0x10, 0x00,  // 3F  63 ?
  0x00, 0x38, 0x44, 0x54, 0x58, 0x40, 0x3C, 0x00,  // 40  64 @
  0x00, 0x38, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x00,  // 41  65 A
  0x00, 0x78, 0x44, 0x78, 0x44, 0x44, 0x78, 0x00,  // 42  66 B
  0x00, 0x38, 0x44, 0x40, 0x40, 0x44, 0x38, 0x00,  // 43  67 C
  0x00, 0x78, 0x44, 0x44, 0x44, 0x44, 0x78, 0x00,  // 44  68 D
  0x00, 0x7C, 0x40, 0x78, 0x40, 0x40, 0x7C, 0x00,  // 45  69 E
  0x00, 0x7C, 0x40, 0x78, 0x40, 0x40, 0x40, 0x00,  // 46  70 F
  0x00, 0x38, 0x44, 0x40, 0x4C, 0x44, 0x38, 0x00,  // 47  71 G
  0x00, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44, 0x00,  // 48  72 H
  0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00,  // 49  73 I
  0x00, 0x04, 0x04, 0x04, 0x04, 0x44, 0x38, 0x00,  // 4A  74 J
  0x00, 0x44, 0x48, 0x50, 0x70, 0x48, 0x44, 0x00,  // 4B  75 K
  0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7C, 0x00,  // 4C  76 L
  0x00, 0x44, 0x6C, 0x54, 0x44, 0x44, 0x44, 0x00,  // 4D  77 M
  0x00, 0x44, 0x64, 0x54, 0x54, 0x4C, 0x44, 0x00,  // 4E  78 N
  0x00, 0x7C, 0x44, 0x44, 0x44, 0x44, 0x7C, 0x00,  // 4F  79 O
  0x00, 0x78, 0x44, 0x44, 0x78, 0x40, 0x40, 0x00,  // 50  80 P
  0x00, 0x38, 0x44, 0x44, 0x54, 0x4C, 0x3C, 0x00,  // 51  81 Q
  0x00, 0x78, 0x44, 0x44, 0x78, 0x48, 0x44, 0x00,  // 52  82 R
  0x00, 0x38, 0x44, 0x30, 0x08, 0x44, 0x38, 0x00,  // 53  83 S
  0x00, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00,  // 54  84 T
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00,  // 55  85 U
  0x00, 0x44, 0x44, 0x44, 0x44, 0x28, 0x10, 0x00,  // 56  86 V
  0x00, 0x44, 0x44, 0x44, 0x54, 0x54, 0x28, 0x00,  // 57  87 W
  0x00, 0x44, 0x28, 0x10, 0x10, 0x28, 0x44, 0x00,  // 58  88 X
  0x00, 0x44, 0x44, 0x28, 0x10, 0x10, 0x10, 0x00,  // 59  89 Y
  0x00, 0x7C, 0x08, 0x10, 0x20, 0x40, 0x7C, 0x00,  // 5A  90 Z
  0x00, 0x38, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00,  // 5B  91 [
  0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00,  // 5C  92 '\'
  0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00,  // 5D  93 ]
  0x00, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00,  // 5E  94 ^
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00,  // 5F  95 _
  0x00, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00,  // 60  96 `
  0x00, 0x00, 0x00, 0x38, 0x48, 0x48, 0x3C, 0x00,  // 61  97 a
  0x00, 0x40, 0x40, 0x70, 0x48, 0x48, 0x70, 0x00,  // 62  98 b
  0x00, 0x00, 0x00, 0x38, 0x40, 0x40, 0x38, 0x00,  // 63  99 c
  0x00, 0x08, 0x08, 0x38, 0x48, 0x48, 0x38, 0x00,  // 64 100 d
  0x00, 0x00, 0x00, 0x38, 0x50, 0x60, 0x38, 0x00,  // 65 101 e
  0x00, 0x18, 0x20, 0x70, 0x20, 0x20, 0x20, 0x00,  // 66 102 f
  0x00, 0x00, 0x00, 0x38, 0x48, 0x38, 0x08, 0x70,  // 67 103 g
  0x00, 0x40, 0x40, 0x70, 0x48, 0x48, 0x48, 0x00,  // 68 104 h
  0x00, 0x10, 0x00, 0x30, 0x10, 0x10, 0x38, 0x00,  // 69 105 i
  0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x48, 0x30,  // 6A 106 j
  0x00, 0x40, 0x40, 0x48, 0x70, 0x50, 0x48, 0x00,  // 6B 107 k
  0x00, 0x30, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00,  // 6C 108 l
  0x00, 0x00, 0x00, 0x78, 0x54, 0x54, 0x54, 0x00,  // 6D 109 m
  0x00, 0x00, 0x00, 0x70, 0x48, 0x48, 0x48, 0x00,  // 6E 110 n
  0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x30, 0x00,  // 6F 111 o
  0x00, 0x00, 0x00, 0x70, 0x48, 0x70, 0x40, 0x40,  // 70 112 p
  0x00, 0x00, 0x00, 0x38, 0x48, 0x38, 0x08, 0x08,  // 71 113 q
  0x00, 0x00, 0x00, 0x50, 0x68, 0x40, 0x40, 0x00,  // 72 114 r
  0x00, 0x00, 0x00, 0x38, 0x60, 0x18, 0x70, 0x00,  // 73 115 s
  0x00, 0x20, 0x20, 0x70, 0x20, 0x20, 0x18, 0x00,  // 74 116 t
  0x00, 0x00, 0x00, 0x48, 0x48, 0x48, 0x38, 0x00,  // 75 117 u
  0x00, 0x00, 0x00, 0x44, 0x28, 0x28, 0x10, 0x00,  // 76 118 v
  0x00, 0x00, 0x00, 0x44, 0x54, 0x54, 0x28, 0x00,  // 77 119 w
  0x00, 0x00, 0x00, 0x48, 0x30, 0x30, 0x48, 0x00,  // 78 120 x
  0x00, 0x00, 0x00, 0x48, 0x48, 0x38, 0x08, 0x70,  // 79 121 y
  0x00, 0x00, 0x00, 0x78, 0x10, 0x20, 0x78, 0x00,  // 7A 122 z
  0x00, 0x18, 0x20, 0x20, 0x40, 0x20, 0x20, 0x18,  // 7B 123 {
  0x00, 0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x10,  // 7C 124 |
  0x00, 0x60, 0x10, 0x10, 0x08, 0x10, 0x10, 0x60,  // 7D 125 }
  0x00, 0x00, 0x20, 0x54, 0x08, 0x00, 0x00, 0x00,  // 7E 126 ~
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // 7F 127
};

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} rgba_t;

typedef struct {
  pin_t pin_D0;
  pin_t pin_D1;
  pin_t pin_D2;
  pin_t pin_D3;
  pin_t pin_A0;
  pin_t pin_A1;
  pin_t pin_A2;
  pin_t pin_A3;

  uint32_t SampleTimeUs_attr; // control
  uint32_t sampleTimeUs_attr; // diagram.json
  uint32_t sampleTimeUs;
  uint32_t SampleTimeMs_attr;
  uint32_t sampleTimeMs_attr;
  uint32_t sampleTimeMs;
  uint32_t TriggerChannel_attr;
  uint32_t triggerChannel_attr;
  uint32_t triggerChannel;
  uint32_t TriggerMode_attr;
  uint32_t triggerMode_attr;
  uint32_t triggerMode;
  uint32_t crt_attr, crtColor;
  uint32_t trace0_attr, trace1_attr, trace2_attr, trace3_attr;
  uint32_t trace0Color, trace1Color, trace2Color, trace3Color;

  buffer_t framebuffer;
  uint32_t fb_w;
  uint32_t fb_h;
  uint32_t serial_h;
  uint32_t serial_x;
  uint32_t serial_y;
  uint8_t countA0;
  uint8_t countA1;
  uint8_t countA2;
  uint8_t countA3;
  float valA0;
  float valA1;
  float valA2;
  float valA3;
  float sample0;
  float lastSample0;
  float sample1;
  float lastSample1;
  float sample2;
  float lastSample2;
  float sample3;
  float lastSample3;
  uint32_t hz0;
  uint32_t hz1;
  uint32_t hz2;
  uint32_t hz3;
  uint32_t dc0;
  uint32_t dc1;
  uint32_t dc2;
  uint32_t dc3;
  float sampleMax0;
  float sampleMin0;
  float sampleMax1;
  float sampleMin1;
  float sampleMax2;
  float sampleMin2;
  float sampleMax3;
  float sampleMin3;
  uint32_t sampleMs;
  uint32_t samplePeriod;
  uint32_t captureUs;
  uint32_t captureMs;
  uint32_t plot_h;
  uint32_t plot_x;
  uint32_t plot_y0;
  uint32_t plot_py0;
  uint32_t plot_y1;
  uint32_t plot_py1;
  uint32_t plot_y2;
  uint32_t plot_py2;
  uint32_t plot_y3;
  uint32_t plot_py3;
  rgba_t crt, txt, lightGray, whiteGray, darkGreen, deepGreen, darkBlue, chipGreen;
  rgba_t trace, trace0, trace1, trace2, trace3;
  rgba_t black, brown, red, orange, gold, green, blue, violet, gray, white, cyan, limeGreen, magenta, purple, yellow;
  timer_t timer;
  uint32_t timerCount;
  bool firstRun;
} chip_state_t;

static void chip_timer_event(void *user_data);
static void draw_plot(chip_state_t *chip);
static uint32_t draw_ch(chip_state_t *chip, uint32_t y_base, uint32_t y_height, float y_val, uint32_t py_val);
static void draw_string(chip_state_t *chip);
static void fill_string(chip_state_t *chip);
static void fill_plot(chip_state_t *chip);
static void calc_hz_duty(chip_state_t *chip);

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_D0 = pin_init("D0", INPUT);
  chip->pin_D1 = pin_init("D1", INPUT);
  chip->pin_D2 = pin_init("D2", INPUT);
  chip->pin_D3 = pin_init("D3", INPUT);
  chip->pin_A0 = pin_init("A0", ANALOG);
  chip->pin_A1 = pin_init("A1", ANALOG);
  chip->pin_A2 = pin_init("A2", ANALOG);
  chip->pin_A3 = pin_init("A3", ANALOG);
  chip->firstRun = true;

  chip->black =     (rgba_t) {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff};
  chip->whiteGray = (rgba_t) {.r = 0xf7, .g = 0xf7, .b = 0xf7, .a = 0xff};
  chip->lightGray = (rgba_t) {.r = 0xb7, .g = 0xb7, .b = 0xb7, .a = 0xff};
  chip->chipGreen = (rgba_t) {.r = 0x08, .g = 0x7f, .b = 0x45, .a = 0xdf};
  chip->darkGreen = (rgba_t) {.r = 0x02, .g = 0x30, .b = 0x20, .a = 0xff};
  chip->deepGreen = (rgba_t) {.r = 0x29, .g = 0x52, .b = 0x40, .a = 0xff};
  chip->darkBlue =  (rgba_t) {.r = 0x03, .g = 0x25, .b = 0x4c, .a = 0xff};
  
  chip->black =     (rgba_t) {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff};
  chip->brown =     (rgba_t) {.r = 0x8f, .g = 0x48, .b = 0x14, .a = 0xff};
  chip->red =       (rgba_t) {.r = 0xff, .g = 0x00, .b = 0x00, .a = 0xff};
  chip->orange =    (rgba_t) {.r = 0xff, .g = 0xa5, .b = 0x00, .a = 0xff};
  chip->gold =      (rgba_t) {.r = 0xff, .g = 0xd7, .b = 0x00, .a = 0xff};
  chip->green =     (rgba_t) {.r = 0x00, .g = 0xa0, .b = 0x00, .a = 0xff};
  chip->blue =      (rgba_t) {.r = 0x00, .g = 0x00, .b = 0xff, .a = 0xff};
  chip->violet =    (rgba_t) {.r = 0xee, .g = 0x82, .b = 0xee, .a = 0xff};
  chip->gray =      (rgba_t) {.r = 0x80, .g = 0x80, .b = 0x80, .a = 0xff};
  chip->white =     (rgba_t) {.r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff};
  chip->cyan =      (rgba_t) {.r = 0x00, .g = 0xff, .b = 0xff, .a = 0xff};
  chip->limeGreen = (rgba_t) {.r = 0x32, .g = 0xcd, .b = 0x32, .a = 0xff};
  chip->magenta =   (rgba_t) {.r = 0xff, .g = 0x00, .b = 0xff, .a = 0xff};
  chip->purple =    (rgba_t) {.r = 0x80, .g = 0x00, .b = 0x80, .a = 0xff};
  chip->yellow =    (rgba_t) {.r = 0xff, .g = 0xff, .b = 0x00, .a = 0xff};

  rgba_t traceColors[15] = {chip->black, chip->brown, chip->red, chip->orange, chip->gold,
                            chip->green, chip->blue, chip->violet, chip->gray, chip->white,
                            chip->cyan, chip->limeGreen, chip->magenta, chip->purple, chip->yellow
                           };

  chip->crt_attr = attr_init("crtColor", 0);
  chip->crtColor = attr_read(chip->crt_attr);
  if (chip->crtColor > 4) chip->crtColor = 4;
  if (chip->crtColor == 0) chip->crt = chip->black; 
  else if (chip->crtColor == 1) chip->crt = chip->whiteGray;
  else if (chip->crtColor == 2) chip->crt = chip->darkGreen;
  else if (chip->crtColor == 3) chip->crt = chip->deepGreen;
  else if (chip->crtColor == 4) chip->crt = chip->darkBlue;

  chip->trace0_attr = attr_init("trace0Color", 0);
  chip->trace0Color = attr_read(chip->trace0_attr);
  if (chip->trace0Color > 14) chip->trace0Color = 14;
  chip->trace0 = traceColors[chip->trace0Color];

  chip->trace1_attr = attr_init("trace1Color", 0);
  chip->trace1Color = attr_read(chip->trace1_attr);
  if (chip->trace1Color > 14) chip->trace1Color = 14;
  chip->trace1 = traceColors[chip->trace1Color];

  chip->trace2_attr = attr_init("trace2Color", 0);
  chip->trace2Color = attr_read(chip->trace2_attr);
  if (chip->trace2Color > 14) chip->trace2Color = 14;
  chip->trace2 = traceColors[chip->trace2Color];

  chip->trace3_attr = attr_init("trace3Color", 0);
  chip->trace3Color = attr_read(chip->trace3_attr);
  if (chip->trace3Color > 14) chip->trace3Color = 14;
  chip->trace3 = traceColors[chip->trace3Color];

   chip->sampleTimeUs_attr = attr_init("sampleTimeUs", 0);
  chip->sampleTimeUs = attr_read(chip->sampleTimeUs_attr);
  if (chip->sampleTimeUs > 400) chip->sampleTimeUs = 400;
  chip->SampleTimeUs_attr = attr_init("SampleTimeUs", chip->sampleTimeUs);

  chip->sampleTimeMs_attr = attr_init("sampleTimeMs", 0);
  chip->sampleTimeMs = attr_read(chip->sampleTimeMs_attr);
  if (chip->sampleTimeMs > 40) chip->sampleTimeMs = 40;
  chip->SampleTimeMs_attr = attr_init("SampleTimeMs", chip->sampleTimeMs);

  chip->triggerChannel_attr = attr_init("triggerChannel", 0);
  chip->triggerChannel = attr_read(chip->triggerChannel_attr);
  if (chip->triggerChannel > 3) chip->triggerChannel = 3;
  chip->TriggerChannel_attr = attr_init("TriggerChannel", chip->triggerChannel);

  chip->triggerMode_attr = attr_init("triggerMode", 0);
  chip->triggerMode = attr_read(chip->triggerMode_attr);
  if (chip->triggerMode > 2) chip->triggerMode = 2;
  chip->TriggerMode_attr = attr_init("TriggerMode", chip->triggerMode);

  chip->sampleMax0 = 0.0;
  chip->sampleMin0 = 5.0;
  chip->sampleMax1 = 0.0;
  chip->sampleMin1 = 5.0;
  chip->sampleMax2 = 0.0;
  chip->sampleMin2 = 5.0;
  chip->sampleMax3 = 0.0;
  chip->sampleMin3 = 5.0;

  chip->serial_h = 60; // 5 lines of text

  chip->framebuffer = framebuffer_init(&chip->fb_w, &chip->fb_h);
  chip->plot_h = chip->fb_h - chip->serial_h;

  chip->samplePeriod = chip->sampleTimeUs + (chip->sampleMs * 1000);
  chip->captureMs = ((chip->fb_w - 2) * chip->sampleTimeUs) / 1000;

  fill_string(chip);
  fill_plot(chip);

  const timer_config_t timer_config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };
  chip->timer = timer_init(&timer_config);
  timer_start(chip->timer, 100, true);
}

void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t*)user_data;

  // analog signals
  chip->valA0 = pin_adc_read(chip->pin_A0);
  chip->valA1 = pin_adc_read(chip->pin_A1);
  chip->valA2 = pin_adc_read(chip->pin_A2);
  chip->valA3 = pin_adc_read(chip->pin_A3);

  // analog signal detected if value > 0 within previous 255 samples
  if (chip->valA0 > 0) chip->countA0 = 255;
  else if (chip->valA0 == 0) {
    if (chip->countA0 > 0) chip->countA0--;
    if (chip->countA0 == 1) {
      chip->sampleMax0 = 0;
      chip->sampleMin0 = 5;
    }
  }
  if (chip->valA1 > 0) chip->countA1 = 255;
  else if (chip->valA1 == 0) {
    if (chip->countA1 > 0) chip->countA1--;
    if (chip->countA1 == 1) {
      chip->sampleMax1 = 0;
      chip->sampleMin1 = 5;
    }
  }
  if (chip->valA2 > 0) chip->countA2 = 255;
  else if (chip->valA2 == 0) {
    if (chip->countA2 > 0) chip->countA2--;
    if (chip->countA2 == 1) {
      chip->sampleMax2 = 0;
      chip->sampleMin2 = 5;
    }
  }
  if (chip->valA3 > 0) chip->countA3 = 255;
  else if (chip->valA3 == 0) {
    if (chip->countA3 > 0) chip->countA3--;
    if (chip->countA3 == 1) {
      chip->sampleMax3 = 0;
      chip->sampleMin3 = 5;
    }
  }
  // detect analog min and max values
  if (chip->sample0 < chip->sampleMin0) chip->sampleMin0 = chip->sample0;
  else if (chip->sample0 > chip->sampleMax0) chip->sampleMax0 = chip->sample0;
  if (chip->sample1 < chip->sampleMin1) chip->sampleMin1 = chip->sample1;
  else if (chip->sample1 > chip->sampleMax1) chip->sampleMax1 = chip->sample1;
  if (chip->sample2 < chip->sampleMin2) chip->sampleMin2 = chip->sample2;
  else if (chip->sample2 > chip->sampleMax2) chip->sampleMax2 = chip->sample2;
  if (chip->sample3 < chip->sampleMin3) chip->sampleMin3 = chip->sample3;
  else if (chip->sample3 > chip->sampleMax3) chip->sampleMax3 = chip->sample3;

  // update channel's sample value with analog or digital readings
  chip->sample0 = (chip->countA0 > 0) ? chip->valA0 : (float)pin_read(chip->pin_D0);
  chip->sample1 = (chip->countA1 > 0) ? chip->valA1 : (float)pin_read(chip->pin_D1);
  chip->sample2 = (chip->countA2 > 0) ? chip->valA2 : (float)pin_read(chip->pin_D2);
  chip->sample3 = (chip->countA3 > 0) ? chip->valA3 : (float)pin_read(chip->pin_D3);

  if (chip->triggerMode == 2) { // falling
    if (chip->plot_x < chip->fb_w - 1) draw_plot(chip);
    if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 0) && (chip->sample0 < chip->lastSample0)) draw_plot(chip);
    else if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 1) && (chip->sample1 < chip->lastSample1)) draw_plot(chip);
    else if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 2) && (chip->sample2 < chip->lastSample2)) draw_plot(chip);
    else if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 3) && (chip->sample3 < chip->lastSample3)) draw_plot(chip);
  }
  else if (chip->triggerMode == 1) { // rising
    if (chip->plot_x < chip->fb_w - 1) draw_plot(chip);
    if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 0) && (chip->sample0 > chip->lastSample0)) draw_plot(chip);
    else if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 1) && (chip->sample1 > chip->lastSample1)) draw_plot(chip);
    else if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 2) && (chip->sample2 > chip->lastSample2)) draw_plot(chip);
    else if ((chip->plot_x == chip->fb_w - 1) && (chip->triggerChannel == 3) && (chip->sample3 > chip->lastSample3)) draw_plot(chip);
  }
  else  draw_plot(chip); // auto triggerMode = 0 (off)

  chip->lastSample0 = chip->sample0;
  chip->lastSample1 = chip->sample1;
  chip->lastSample2 = chip->sample2;
  chip->lastSample3 = chip->sample3;

  calc_hz_duty(chip);

if (chip->firstRun ||
    (chip->sampleTimeUs != attr_read(chip->SampleTimeUs_attr)) ||
    (chip->sampleMs != attr_read(chip->SampleTimeMs_attr))) {
    chip->sampleTimeUs = attr_read(chip->SampleTimeUs_attr);
    chip->sampleMs = attr_read(chip->SampleTimeMs_attr);
    chip->triggerChannel = attr_read(chip->TriggerChannel_attr);
    chip->triggerMode = attr_read(chip->TriggerMode_attr);

    if (chip->sampleTimeUs + chip->sampleMs < 10) chip->sampleTimeUs = 10;
    chip->samplePeriod = chip->sampleTimeUs + (chip->sampleMs * 1000);
    timer_start(chip->timer, chip->samplePeriod, true);
    chip->captureUs = (chip->fb_w - 2) * (chip->sampleTimeUs + (chip->sampleMs * 1000));
    chip->captureMs = chip->captureUs / 1000;
    chip->firstRun = false;
  }

  if (chip->triggerChannel != attr_read(chip->TriggerChannel_attr)) chip->triggerChannel = attr_read(chip->TriggerChannel_attr);
  if (chip->triggerMode != attr_read(chip->TriggerMode_attr)) chip->triggerMode = attr_read(chip->TriggerMode_attr);

  if (chip->sampleMs == 0 && chip->timerCount % (255 * (41 - (chip->sampleTimeUs / 10))) == 0) draw_string(chip);
  else if (chip->sampleMs > 0) draw_string(chip);

  chip->timerCount++;
}

void draw_string(chip_state_t *chip) {
  uint8_t ch, sb = 0x20, sc = 0x20, sd = 0x20, se = 0x20;
  ch = chip->triggerChannel;
  (ch == 0) ? sb = 0x3e : (ch == 1) ? sc = 0x3e : (ch == 2) ? sd = 0x3e : (ch == 3) ? se = 0x3e : 0x20;
  char serial_a[32] = "                               ";
  char serial_b[32] = "                               ";
  char serial_c[32] = "                               ";
  char serial_d[32] = "                               ";
  char serial_e[32] = "                               ";
  snprintf (serial_a, 32, " %6d S/s  %5d ms              ", 1000000 / (chip->sampleTimeUs + (chip->sampleMs * 1000)), chip->captureMs);
  if (chip->countA0 == 0) snprintf (serial_b, 32, "%c D0 %4d Hz  %3d%% Duty        ", sb, chip->hz0, chip->dc0);
  else                    snprintf (serial_b, 32, "%c A0  %1.1f Vmin %1.1f Vmax    ", sb, chip->sampleMin0, chip->sampleMax0);
  if (chip->countA1 == 0) snprintf (serial_c, 32, "%c D1 %4d Hz  %3d%% Duty        ", sc, chip->hz1, chip->dc1);
  else                    snprintf (serial_c, 32, "%c A1  %1.1f Vmin %1.1f Vmax    ", sc, chip->sampleMin1, chip->sampleMax1);
  if (chip->countA2 == 0) snprintf (serial_d, 32, "%c D2 %4d Hz  %3d%% Duty        ", sd, chip->hz2, chip->dc2);
  else                    snprintf (serial_d, 32, "%c A2  %1.1f Vmin %1.1f Vmax    ", sd, chip->sampleMin2, chip->sampleMax2);
  if (chip->countA3 == 0) snprintf (serial_e, 32, "%c D3 %4d Hz  %3d%% Duty        ", se, chip->hz3, chip->dc3);
  else                    snprintf (serial_e, 32, "%c A3  %1.1f Vmin %1.1f Vmax    ", se, chip->sampleMin3, chip->sampleMax3);
  rgba_t color;
  int ascii, yy;
  chip->serial_y = chip->fb_h - chip->serial_h + 2;
  for (int c = 0; c < 130; c++) {  // 130
    chip->serial_x = (c % 26) * 9;
    ascii = (c < 26) ? serial_a[c % 26] : (c < 52) ? serial_b[c % 26] : (c < 78) ? serial_c[c % 26] : (c < 104) ? serial_d[c % 26] : serial_e[c % 26];
    yy = (c < 26) ? 1 : (c < 52) ? 12 : (c < 78) ? 23 : (c < 104) ? 34 : 45;
    chip->txt = ((yy -1) / 11 == chip->triggerChannel + 1) ? chip->white : chip->lightGray;
    const uint8_t *bitmap = font8x8[ascii];
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        color = (bitmap[y] & (1 << (8 - x))) ? chip->txt : chip->chipGreen;
        buffer_write(chip->framebuffer, (chip->fb_w * 4 * (y + yy + chip->serial_y)) + ((x + 10 + chip->serial_x) * 4), &color, sizeof(color));
      }
    }
  }
}

uint32_t draw_ch(chip_state_t *chip, uint32_t y_base, uint32_t y_height, float y_val, uint32_t py_val) {
  rgba_t color;
  uint32_t plot_y = y_base - y_val * y_height;
  for (int y = y_base - y_height; y < y_base + 1; y += 1) {
    color = ((plot_y >= y_base - y_height && plot_y <= y_base + 1) &&
             (y < plot_y && y < py_val) ||
             (y > plot_y && y > py_val) ||
             (chip->plot_x == chip->fb_w - 1) ||
             (chip->plot_x == 0)) ? chip->crt : chip->trace;
    buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + (chip->plot_x * 4), &color, sizeof(color));
    if (chip->plot_x + 8 < chip->fb_w && chip->sampleMs) buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + ((chip->plot_x + 8) * 4), &chip->crt, sizeof(color));
  }
  return plot_y;
}

void draw_plot(chip_state_t *chip) {
  chip->trace = chip->trace0; 
  chip->plot_py0 = draw_ch(chip, 24, 20, (chip->countA0 > 0) ? chip->sample0 * 0.2 : chip->sample0, chip->plot_py0);
  chip->trace = chip->trace1; 
  chip->plot_py1 = draw_ch(chip, 50, 20, (chip->countA1 > 0) ? chip->sample1 * 0.2 : chip->sample1, chip->plot_py1);
  chip->trace = chip->trace2; 
  chip->plot_py2 = draw_ch(chip, 76, 20, (chip->countA2 > 0) ? chip->sample2 * 0.2 : chip->sample2, chip->plot_py2);
  chip->trace = chip->trace3; 
  chip->plot_py3 = draw_ch(chip, 102, 20, (chip->countA3 > 0) ? chip->sample3 * 0.2 : chip->sample3, chip->plot_py3);
  chip->plot_x = (chip->plot_x + 1) % chip->fb_w;
}

void fill_string(chip_state_t *chip) {
  for (int x = 0; x < chip->fb_w; x += 1) {
    for (int y = chip->fb_h - chip->serial_h; y < chip->fb_h; y += 1) {
      buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + (x * 4), &chip->chipGreen, sizeof(chip->chipGreen));
    }
  }
}

void fill_plot(chip_state_t *chip) {
  for (int x = 0; x < chip->fb_w; x += 1) {
    for (int y = 0; y < chip->fb_h - chip->serial_h; y += 1) {
      buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + (x * 4), &chip->crt, sizeof(chip->crt));
    }
  }
}

void calc_hz_duty(chip_state_t *chip) {
  static uint32_t ppy0, ppy1, ppy2, ppy3;
  static uint32_t period0, period1, period2, period3;
  static uint32_t t0, t1, t2, t3;
  static uint32_t tt0, tt1, tt2, tt3;

  if (chip->plot_x == 0) {
    t0 = tt0 = 0;
    t1 = tt1 = 0;
    t2 = tt2 = 0;
    t3 = tt3 = 0;
  }
  if (chip->triggerMode == 1 && chip->plot_py0 > ppy0 && t0 == 0 && tt0 == 0) t0 = chip->plot_x;
  else if (chip->triggerMode == 1 && chip->plot_py0 < ppy0 && t0 > 0 && tt0 == 0) tt0 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py0 < ppy0 && t0 == 0 && tt0 == 0) t0 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py0 > ppy0 && t0 > 0 && tt0 == 0) tt0 = chip->plot_x;
  if (t0 > 0 && tt0 > 0) period0 = tt0;
  if (period0 > 0) chip->hz0 = 1000000 / (chip->samplePeriod * period0);
  if (t0 > 0 && tt0 > 0 && period0 > 0) chip->dc0 = (chip->triggerMode == 2) ? ((tt0 - t0) * 100) / period0 : (t0 * 100) / period0;

  if (chip->triggerMode == 1 && chip->plot_py1 > ppy1 && t1 == 0 && tt1 == 0) t1 = chip->plot_x;
  else if (chip->triggerMode == 1 && chip->plot_py1 < ppy1 && t1 > 0 && tt1 == 0) tt1 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py1 < ppy1 && t1 == 0 && tt1 == 0) t1 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py1 > ppy1 && t1 > 0 && tt1 == 0) tt1 = chip->plot_x;
  if (t1 > 0 && tt1 > 0) period1 = tt1;
  if (period1 > 0) chip->hz1 = 1000000 / (chip->samplePeriod * period1);
  if (t1 > 0 && tt1 > 0 && period1 > 0) chip->dc1 = (chip->triggerMode == 2) ? ((tt1 - t1) * 100) / period1 : (t1 * 100) / period1;

  if (chip->triggerMode == 1 && chip->plot_py2 > ppy2 && t2 == 0 && tt2 == 0) t2 = chip->plot_x;
  else if (chip->triggerMode == 1 && chip->plot_py2 < ppy2 && t2 > 0 && tt2 == 0) tt2 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py2 < ppy2 && t2 == 0 && tt2 == 0) t2 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py2 > ppy2 && t2 > 0 && tt2 == 0) tt2 = chip->plot_x;
  if (t2 > 0 && tt2 > 0) period2 = tt2;
  if (period2 > 0) chip->hz2 = 1000000 / (chip->samplePeriod * period2);
  if (t2 > 0 && tt2 > 0 && period2 > 0) chip->dc2 = (chip->triggerMode == 2) ? ((tt2 - t2) * 100) / period2 : (t2 * 100) / period2;

  if (chip->triggerMode == 1 && chip->plot_py3 > ppy3 && t3 == 0 && tt3 == 0) t3 = chip->plot_x;
  else if (chip->triggerMode == 1 && chip->plot_py3 < ppy3 && t3 > 0 && tt3 == 0) tt3 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py3 < ppy3 && t3 == 0 && tt3 == 0) t3 = chip->plot_x;
  else if (chip->triggerMode == 2 && chip->plot_py3 > ppy3 && t3 > 0 && tt3 == 0) tt3 = chip->plot_x;
  if (t3 > 0 && tt3 > 0) period3 = tt3;
  if (period3 > 0) chip->hz3 = 1000000 / (chip->samplePeriod * period3);
  if (t3 > 0 && tt3 > 0 && period3 > 0) chip->dc3 = (chip->triggerMode == 2) ? ((tt3 - t3) * 100) / period3 : (t3 * 100) / period3;

  ppy0 = chip->plot_py0;
  ppy1 = chip->plot_py1;
  ppy2 = chip->plot_py2;
  ppy3 = chip->plot_py3;
}
