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
    char file_type[3];    // "Magic number"
    unsigned int width;   // Image width, ASCII decimal
    unsigned int height;  // Image height, ASCII decimal
    unsigned int maxval;  // Maximum color value (Maxval), ASCII decimal
  } Header;

  struct {
    Pixel* pixel_data;  // Image pixel data
  } Body;
} PPMFile;

int read_ppm_file(const char* ppm_file_path);

const unsigned int get_width();
const unsigned int get_height();
void free_pixel_data();
Pixel* get_pixel_data();