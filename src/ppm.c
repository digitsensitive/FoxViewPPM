#include "ppm.h"

PPMData ppm_data;

int read_ppm_file(const char* ppm_file_path) {
  FILE* ppm_file;

  ppm_file = fopen(ppm_file_path, "r");

  if (ppm_file == NULL) {
    printf("Memory allocation for FILE pointer failed!\n");
    return 1;
  }

  /* PPM Header */
  // File Type
  fscanf(ppm_file, "%2s", ppm_data.PPMHeader.file_type);
  ppm_data.PPMHeader.file_type[2] = '\0';  // Null-terminate the string

  if (ppm_data.PPMHeader.file_type[0] != 'P' ||
      (ppm_data.PPMHeader.file_type[1] != '1' &&
       ppm_data.PPMHeader.file_type[1] != '3')) {
    printf("Invalid PPM file format!\n");
    fclose(ppm_file);
    return 1;
  }

  // Width and Height
  int result_image_size = fscanf(ppm_file, "%d %d", &ppm_data.PPMHeader.width,
                                 &ppm_data.PPMHeader.height);

  if (result_image_size != 2) {
    printf("Invalid width and/or height (must be integers)!\n");
    return 1;
  }

  // Maximum color value
  int result_maxval = fscanf(ppm_file, "%d", &ppm_data.PPMHeader.maxval);

  if (result_maxval != 1 || ppm_data.PPMHeader.maxval >= 65536 ||
      ppm_data.PPMHeader.maxval <= 0) {
    printf("Invalid maxval value (must be integer and > 0 and < 65536)!\n");
    return 1;
  }

  /* PPM Body */
  // Allocate memory for 2D Pixel-Data-Matrix
  ppm_data.PPMBody.pixel_data = (Pixel*)malloc(
      ppm_data.PPMHeader.width * ppm_data.PPMHeader.height * sizeof(Pixel));

  if (ppm_data.PPMBody.pixel_data == NULL) {
    printf("Memory allocation for pixel data failed!\n");
    return 1;
  }

  for (int y = 0; y < ppm_data.PPMHeader.height; y++) {
    for (int x = 0; x < ppm_data.PPMHeader.width; x++) {
      int index = y * ppm_data.PPMHeader.width + x;

      int result_pixel =
          fscanf(ppm_file, "%d %d %d", &ppm_data.PPMBody.pixel_data[index].r,
                 &ppm_data.PPMBody.pixel_data[index].g,
                 &ppm_data.PPMBody.pixel_data[index].b);

      if (result_pixel != 3) {
        printf("Invalid pixel data (must be integers)!\n");
        return 1;
      }
    }
  }

  fclose(ppm_file);

  return 0;
}

const unsigned int get_width() { return ppm_data.PPMHeader.width; }
const unsigned int get_height() { return ppm_data.PPMHeader.height; }

Pixel* get_pixel_data() { return ppm_data.PPMBody.pixel_data; }