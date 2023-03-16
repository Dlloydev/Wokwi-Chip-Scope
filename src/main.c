// Digital Plot3 Chip
// by David Lloyd, March 2023.

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <wchar.h>

const uint8_t font8x8[128][8] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0000 (nul)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0001
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0002
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0003
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0004
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0005
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0006
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0007
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0008
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0009
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000A
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000B
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000C
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000D
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000E
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0010
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0011
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0012
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0013
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0014
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0015
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0016
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0017
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0018
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0019
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001A
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001B
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001C
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001D
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001E
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0020 (space)
  { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},   // U+0021 (!)
  { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0022 (")
  { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},   // U+0023 (#)
  { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},   // U+0024 ($)
  { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},   // U+0025 (%)
  { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},   // U+0026 (&)
  { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0027 (')
  { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},   // U+0028 (()
  { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},   // U+0029 ())
  { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},   // U+002A (*)
  { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},   // U+002B (+)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+002C (,)
  { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},   // U+002D (-)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+002E (.)
  { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},   // U+002F (/)
  { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},   // U+0030 (0)
  { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},   // U+0031 (1)
  { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},   // U+0032 (2)
  { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},   // U+0033 (3)
  { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},   // U+0034 (4)
  { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},   // U+0035 (5)
  { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},   // U+0036 (6)
  { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},   // U+0037 (7)
  { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},   // U+0038 (8)
  { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},   // U+0039 (9)
  { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+003A (:)
  { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+003B (;)
  { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},   // U+003C (<)
  { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},   // U+003D (=)
  { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},   // U+003E (>)
  { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},   // U+003F (?)
  { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},   // U+0040 (@)
  { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0041 (A)
  { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},   // U+0042 (B)
  { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},   // U+0043 (C)
  { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},   // U+0044 (D)
  { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},   // U+0045 (E)
  { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},   // U+0046 (F)
  { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},   // U+0047 (G)
  { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},   // U+0048 (H)
  { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0049 (I)
  { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},   // U+004A (J)
  { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},   // U+004B (K)
  { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},   // U+004C (L)
  { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},   // U+004D (M)
  { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},   // U+004E (N)
  { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},   // U+004F (O)
  { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},   // U+0050 (P)
  { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},   // U+0051 (Q)
  { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},   // U+0052 (R)
  { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},   // U+0053 (S)
  { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0054 (T)
  { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},   // U+0055 (U)
  { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0056 (V)
  { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},   // U+0057 (W)
  { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},   // U+0058 (X)
  { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},   // U+0059 (Y)
  { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},   // U+005A (Z)
  { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},   // U+005B ([)
  { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},   // U+005C (\)
  { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},   // U+005D (])
  { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},   // U+005E (^)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   // U+005F (_)
  { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0060 (`)
  { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},   // U+0061 (a)
  { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},   // U+0062 (b)
  { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},   // U+0063 (c)
  { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},   // U+0064 (d)
  { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},   // U+0065 (e)
  { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},   // U+0066 (f)
  { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0067 (g)
  { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},   // U+0068 (h)
  { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0069 (i)
  { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},   // U+006A (j)
  { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},   // U+006B (k)
  { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+006C (l)
  { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},   // U+006D (m)
  { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},   // U+006E (n)
  { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+006F (o)
  { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},   // U+0070 (p)
  { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},   // U+0071 (q)
  { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},   // U+0072 (r)
  { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},   // U+0073 (s)
  { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+0074 (t)
  { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},   // U+0075 (u)
  { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0076 (v)
  { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},   // U+0077 (w)
  { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},   // U+0078 (x)
  { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0079 (y)
  { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},   // U+007A (z)
  { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},   // U+007B ({)
  { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},   // U+007C (|)
  { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},   // U+007D (})
  { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007E (~)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}    // U+007F
}; // https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h

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

  uint32_t sampleTimeUs_attr;
  uint32_t sampleTimeUs;
  uint32_t sampleTimeMs_attr;
  uint32_t sampleTimeMs;
  uint32_t triggerChannel_attr;
  uint32_t triggerChannel;
  uint32_t triggerMode_attr;
  uint32_t triggerMode;

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
  rgba_t white;
  rgba_t green;
  rgba_t background;
  timer_t timer;
  uint32_t timer_count;
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

  chip->sampleTimeUs_attr = attr_init("sampleTimeUs", 100);
  chip->sampleTimeMs_attr = attr_init("sampleTimeMs", 0);
  chip->triggerChannel_attr = attr_init("triggerChannel", 0);
  chip->triggerMode_attr = attr_init("triggerMode", 1);

  uint32_t sampleTimeUs = chip->sampleTimeUs_attr;
  uint32_t sampleTimeMs = chip->sampleTimeMs_attr;
  uint32_t triggerChannel = chip->triggerChannel_attr;
  uint32_t triggerMode = chip->triggerMode_attr;

  chip->white = (rgba_t) {
    .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff
  };
  chip->green = (rgba_t) {
    .r = 0x08, .g = 0x7f, .b = 0x45, .a = 0xff
  };
  chip->background = (rgba_t) {
    .r = 0xf7, .g = 0xf7, .b = 0xf7, .a = 0xff
  };

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
  printf("Framebuffer: width=%d, height=%d\n", chip->fb_w, chip->fb_h);
  chip->plot_h = chip->fb_h - chip->serial_h;

  chip->sampleTimeUs = attr_read(chip->sampleTimeUs_attr);
  chip->sampleMs = attr_read(chip->sampleTimeMs_attr);

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

  chip->valA0 = pin_adc_read(chip->pin_A0);
  if (chip->valA0 > 0) chip->countA0 = 255;
  else if (chip->valA0 == 0) {
    if (chip->countA0 > 0) chip->countA0--;
    if (chip->countA0 == 1) {
      chip->sampleMax0 = 0;
      chip->sampleMin0 = 5;
    }
  }
  chip->valA1 = pin_adc_read(chip->pin_A1);
  if (chip->valA1 > 0) chip->countA1 = 255;
  else if (chip->valA1 == 0) {
    if (chip->countA1 > 0) chip->countA1--;
    if (chip->countA1 == 1) {
      chip->sampleMax1 = 0;
      chip->sampleMin1 = 5;
    }
  }
  chip->valA2 = pin_adc_read(chip->pin_A2);
  if (chip->valA2 > 0) chip->countA2 = 255;
  else if (chip->valA2 == 0) {
    if (chip->countA2 > 0) chip->countA2--;
    if (chip->countA2 == 1) {
      chip->sampleMax2 = 0;
      chip->sampleMin2 = 5;
    }
  }
  chip->valA3 = pin_adc_read(chip->pin_A3);
  if (chip->valA3 > 0) chip->countA3 = 255;
  else if (chip->valA3 == 0) {
    if (chip->countA3 > 0) chip->countA3--;
    if (chip->countA3 == 1) {
      chip->sampleMax3 = 0;
      chip->sampleMin3 = 5;
    }
  }

  chip->sample0 = (chip->countA0 > 0) ? chip->valA0 : pin_read(chip->pin_D0);
  if (chip->sample0 < chip->sampleMin0) chip->sampleMin0 = chip->sample0;
  else if (chip->sample0 > chip->sampleMax0) chip->sampleMax0 = chip->sample0;

  chip->sample1 = (chip->countA1 > 0) ? chip->valA1 : pin_read(chip->pin_D1);
  if (chip->sample1 < chip->sampleMin1) chip->sampleMin1 = chip->sample1;
  else if (chip->sample1 > chip->sampleMax1) chip->sampleMax1 = chip->sample1;

  chip->sample2 = (chip->countA2 > 0) ? chip->valA2 : pin_read(chip->pin_D2);
  if (chip->sample2 < chip->sampleMin2) chip->sampleMin2 = chip->sample2;
  else if (chip->sample2 > chip->sampleMax2) chip->sampleMax2 = chip->sample2;

  chip->sample3 = (chip->countA3 > 0) ? chip->valA3 : pin_read(chip->pin_D3);
  if (chip->sample3 < chip->sampleMin3) chip->sampleMin3 = chip->sample3;
  else if (chip->sample3 > chip->sampleMax3) chip->sampleMax3 = chip->sample3;

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

  if ((chip->sampleTimeUs != attr_read(chip->sampleTimeUs_attr)) ||
      (chip->sampleMs != attr_read(chip->sampleTimeMs_attr))) {
    chip->sampleTimeUs = attr_read(chip->sampleTimeUs_attr);
    chip->sampleMs = attr_read(chip->sampleTimeMs_attr);
    if (chip->sampleTimeUs + chip->sampleMs < 10) chip->sampleTimeUs = 10;
    chip->samplePeriod = chip->sampleTimeUs + (chip->sampleMs * 1000);
    timer_start(chip->timer, chip->samplePeriod, true);
    chip->captureUs = (chip->fb_w - 2) * (chip->sampleTimeUs + (chip->sampleMs * 1000));
    chip->captureMs = chip->captureUs / 1000;
  }
  if (chip->triggerChannel != attr_read(chip->triggerChannel_attr)) chip->triggerChannel = attr_read(chip->triggerChannel_attr);
  if (chip->triggerMode != attr_read(chip->triggerMode_attr)) chip->triggerMode = attr_read(chip->triggerMode_attr);

  if ((chip->timer_count & 0xff) == 0) draw_string(chip);
  calc_hz_duty(chip);
  chip->timer_count++;
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
  if (chip->countA0 == 0) snprintf (serial_b, 32, "%c D0 %4d Hz  %3d%% Duty     ", sb, chip->hz0, chip->dc0);
  else                    snprintf (serial_b, 32, "%c A0  %1.1f Vmin %1.1f Vmax ", sb, chip->sampleMin0, chip->sampleMax0);
  if (chip->countA1 == 0) snprintf (serial_c, 32, "%c D1 %4d Hz  %3d%% Duty     ", sc, chip->hz1, chip->dc1);
  else                    snprintf (serial_c, 32, "%c A1  %1.1f Vmin %1.1f Vmax ", sc, chip->sampleMin1, chip->sampleMax1);
  if (chip->countA2 == 0) snprintf (serial_d, 32, "%c D2 %4d Hz  %3d%% Duty     ", sd, chip->hz2, chip->dc2);
  else                    snprintf (serial_d, 32, "%c A2  %1.1f Vmin %1.1f Vmax ", sd, chip->sampleMin2, chip->sampleMax2);
  if (chip->countA3 == 0) snprintf (serial_e, 32, "%c D3 %4d Hz  %3d%% Duty     ", se, chip->hz3, chip->dc3);
  else                    snprintf (serial_e, 32, "%c A3  %1.1f Vmin %1.1f Vmax ", se, chip->sampleMin3, chip->sampleMax3);
  rgba_t color;
  int ascii, yy;
  chip->serial_y = chip->fb_h - chip->serial_h + 2;
  for (int c = 0; c < 130; c++) {  // 130
    chip->serial_x = (c % 26) * 9;
    ascii = (c < 26) ? serial_a[c % 26] : (c < 52) ? serial_b[c % 26] : (c < 78) ? serial_c[c % 26] : (c < 104) ? serial_d[c % 26] : serial_e[c % 26];
    yy = (c < 26) ? 1 : (c < 52) ? 12 : (c < 78) ? 23 : (c < 104) ? 34 : 45;
    const uint8_t *bitmap = font8x8[ascii];
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        color = (bitmap[y] & (1 << x)) ? chip->white : chip->green;
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
             (chip->plot_x == 0)) ? chip->background : chip->green;
    buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + (chip->plot_x * 4), &color, sizeof(color));
  }
  return plot_y;
}

void draw_plot(chip_state_t *chip) {
  chip->plot_py0 = draw_ch(chip, 24, 20, (chip->countA0 > 0) ? chip->sample0 * 0.2 : chip->sample0, chip->plot_py0);
  chip->plot_py1 = draw_ch(chip, 50, 20, (chip->countA1 > 0) ? chip->sample1 * 0.2 : chip->sample1, chip->plot_py1);
  chip->plot_py2 = draw_ch(chip, 76, 20, (chip->countA2 > 0) ? chip->sample2 * 0.2 : chip->sample2, chip->plot_py2);
  chip->plot_py3 = draw_ch(chip, 102, 20, (chip->countA3 > 0) ? chip->sample3 * 0.2 : chip->sample3, chip->plot_py3);
  chip->plot_x = (chip->plot_x + 1) % chip->fb_w;
}

void fill_string(chip_state_t *chip) {
  for (int x = 0; x < chip->fb_w; x += 1) {
    for (int y = chip->fb_h - chip->serial_h; y < chip->fb_h; y += 1) {
      buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + (x * 4), &chip->green, sizeof(chip->green));
    }
  }
}

void fill_plot(chip_state_t *chip) {
  for (int x = 0; x < chip->fb_w; x += 1) {
    for (int y = 0; y < chip->fb_h - chip->serial_h; y += 1) {
      buffer_write(chip->framebuffer, (chip->fb_w * 4 * y) + (x * 4), &chip->background, sizeof(chip->background));
    }
  }
}

void calc_hz_duty(chip_state_t *chip) {
  static uint32_t ppy0, ppy1, ppy2, ppy3;
  static uint32_t period0, period1, period2, period3;
  static uint32_t t0, t1, t2, t3;
  static uint32_t tt0, tt1, tt2, tt3;

  if (chip->triggerChannel != 0 || (chip->plot_x == 0)) t0 = tt0 = 0;
  if (chip->triggerChannel != 1 || (chip->plot_x == 0)) t1 = tt1 = 0;
  if (chip->triggerChannel != 2 || (chip->plot_x == 0)) t2 = tt2 = 0;
  if (chip->triggerChannel != 3 || (chip->plot_x == 0)) t3 = tt3 = 0;

  if (chip->triggerChannel == 0) {
    if (chip->triggerMode == 1 && chip->plot_py0 > ppy0 && t0 == 0 && tt0 == 0) t0 = chip->plot_x;
    else if (chip->triggerMode == 1 && chip->plot_py0 < ppy0 && t0 > 0 && tt0 == 0) tt0 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py0 < ppy0 && t0 == 0 && tt0 == 0) t0 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py0 > ppy0 && t0 > 0 && tt0 == 0) tt0 = chip->plot_x;
    if (t0 > 0 && tt0 > 0) period0 = tt0;
    if (period0 > 0) chip->hz0 = 1000000 / (chip->samplePeriod * period0);
    if (t0 > 0 && tt0 > 0 && period0 > 0) chip->dc0 = (chip->triggerMode == 2) ? ((tt0 - t0) * 100) / period0 : (t0 * 100) / period0;
  }

  else if (chip->triggerChannel == 1) {
    if (chip->triggerMode == 1 && chip->plot_py1 > ppy1 && t1 == 0 && tt1 == 0) t1 = chip->plot_x;
    else if (chip->triggerMode == 1 && chip->plot_py1 < ppy1 && t1 > 0 && tt1 == 0) tt1 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py1 < ppy1 && t1 == 0 && tt1 == 0) t1 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py1 > ppy1 && t1 > 0 && tt1 == 0) tt1 = chip->plot_x;
    if (t1 > 0 && tt1 > 0) period1 = tt1;
    if (period1 > 0) chip->hz1 = 1000000 / (chip->samplePeriod * period1);
    if (t1 > 0 && tt1 > 0 && period1 > 0) chip->dc1 = (chip->triggerMode == 2) ? ((tt1 - t1) * 100) / period1 : (t1 * 100) / period1;
  }

  else if (chip->triggerChannel == 2) {
    if (chip->triggerMode == 1 && chip->plot_py2 > ppy2 && t2 == 0 && tt2 == 0) t2 = chip->plot_x;
    else if (chip->triggerMode == 1 && chip->plot_py2 < ppy2 && t2 > 0 && tt2 == 0) tt2 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py2 < ppy2 && t2 == 0 && tt2 == 0) t2 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py2 > ppy2 && t2 > 0 && tt2 == 0) tt2 = chip->plot_x;
    if (t2 > 0 && tt2 > 0) period2 = tt2;
    if (period2 > 0) chip->hz2 = 1000000 / (chip->samplePeriod * period2);
    if (t2 > 0 && tt2 > 0 && period2 > 0) chip->dc2 = (chip->triggerMode == 2) ? ((tt2 - t2) * 100) / period2 : (t2 * 100) / period2;
  }

  else if (chip->triggerChannel == 3) {
    if (chip->triggerMode == 1 && chip->plot_py3 > ppy3 && t3 == 0 && tt3 == 0) t3 = chip->plot_x;
    else if (chip->triggerMode == 1 && chip->plot_py3 < ppy3 && t3 > 0 && tt3 == 0) tt3 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py3 < ppy3 && t3 == 0 && tt3 == 0) t3 = chip->plot_x;
    else if (chip->triggerMode == 2 && chip->plot_py3 > ppy3 && t3 > 0 && tt3 == 0) tt3 = chip->plot_x;
    if (t3 > 0 && tt3 > 0) period3 = tt3;
    if (period3 > 0) chip->hz3 = 1000000 / (chip->samplePeriod * period3);
    if (t3 > 0 && tt3 > 0 && period3 > 0) chip->dc3 = (chip->triggerMode == 2) ? ((tt3 - t3) * 100) / period3 : (t3 * 100) / period3;
  }

  ppy0 = chip->plot_py0;
  ppy1 = chip->plot_py1;
  ppy2 = chip->plot_py2;
  ppy3 = chip->plot_py3;
}
