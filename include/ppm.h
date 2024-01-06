#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MAXVAL 65536

typedef struct {
  const unsigned char r;  // Red
  const unsigned char g;  // Green
  const unsigned char b;  // Blue
} Pixel;

typedef struct {
  struct {
    char file_type[3];         // "Magic number"(P6 raw format, P3 plain format)
    const unsigned int width;  // Image width, ASCII decimal
    const unsigned int height;  // Image height, ASCII decimal
    const unsigned int maxval;  // Maximum color value (Maxval), ASCII decimal
  } PPMHeader;

  struct {
    Pixel* pixel_data;  // Image pixel data
  } PPMBody;
} PPMData;

int read_ppm_file(const char* ppm_file_path);

const unsigned int get_width();
const unsigned int get_height();
Pixel* get_pixel_data();