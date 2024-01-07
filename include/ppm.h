#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MAXVAL 65536

typedef struct {
  unsigned char r;  // Red
  unsigned char g;  // Green
  unsigned char b;  // Blue
} Pixel;

typedef struct {
  struct {
    char file_type[3];    // "Magic number"(P6 raw format, P3 plain format)
    unsigned int width;   // Image width, ASCII decimal
    unsigned int height;  // Image height, ASCII decimal
    unsigned int maxval;  // Maximum color value (Maxval), ASCII decimal
  } PPMHeader;

  struct {
    Pixel* pixel_data;  // Image pixel data
  } PPMBody;
} PPMData;

int read_ppm_file(const char* ppm_file_path);

const unsigned int get_width();
const unsigned int get_height();
Pixel* get_pixel_data();