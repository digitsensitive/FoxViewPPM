#include "ppm.h"

PPMData ppm_data;

int read_ppm_file(const char* ppm_file_path) {
  FILE* ppm_file;

  ppm_file = fopen(ppm_file_path, "rb");

  if (ppm_file == NULL) {
    printf("Memory allocation for FILE pointer failed!\n");
    return 1;
  }

  /* ------------------------- PPM Header ------------------------- */
  // File Type
  fscanf(ppm_file, "%2s", ppm_data.PPMHeader.file_type);
  ppm_data.PPMHeader.file_type[2] = '\0';  // Null-terminate the string

  if (ppm_data.PPMHeader.file_type[0] != 'P' ||
      (ppm_data.PPMHeader.file_type[1] != '1' &&
       ppm_data.PPMHeader.file_type[1] != '2' &&
       ppm_data.PPMHeader.file_type[1] != '3' &&
       ppm_data.PPMHeader.file_type[1] != '4' &&
       ppm_data.PPMHeader.file_type[1] != '5' &&
       ppm_data.PPMHeader.file_type[1] != '6')) {
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
  ppm_data.PPMHeader.maxval = 0;  // Default value of maxval is 0

  if (ppm_data.PPMHeader.file_type[1] == '2' ||
      ppm_data.PPMHeader.file_type[1] == '3' ||
      ppm_data.PPMHeader.file_type[1] == '5' ||
      ppm_data.PPMHeader.file_type[1] == '6') {
    int result_maxval = fscanf(ppm_file, "%d", &ppm_data.PPMHeader.maxval);

    if (result_maxval != 1 || ppm_data.PPMHeader.maxval >= 65536 ||
        ppm_data.PPMHeader.maxval <= 0) {
      printf("Invalid maxval value (must be integer and > 0 and < 65536)!\n");
      return 1;
    }
  }

  /* ------------------------- PPM Body ------------------------- */
  // Allocate memory for pixel data
  ppm_data.PPMBody.pixel_data = (Pixel*)malloc(
      ppm_data.PPMHeader.width * ppm_data.PPMHeader.height * sizeof(Pixel));

  if (ppm_data.PPMBody.pixel_data == NULL) {
    printf("Memory allocation for pixel data failed!\n");
    return 1;
  }

  for (int y = 0; y < ppm_data.PPMHeader.height; y++) {
    for (int x = 0; x < ppm_data.PPMHeader.width; x++) {
      int index = y * ppm_data.PPMHeader.width + x;

      switch (ppm_data.PPMHeader.file_type[1]) {
        case '1':
          /* ----- Portable BitMap, PBM, ASCII -----*/
        case '4':
          /* ----- Portable BitMap, PBM, Binary -----*/
          // Get current pixel value, ASCII "0" or "1"
          const unsigned char value_p1;
          int result_pixel_p1_p4 = fscanf(ppm_file, "%d", &value_p1);

          if (result_pixel_p1_p4 > 1 || result_pixel_p1_p4 < 0) {
            printf("P1 Body: Invalid pixel data (must be integers)!\n");
            return 1;
          }

          // Traditionally "0" refers to white while "1" refers to black.
          const unsigned char value_rgb = value_p1 == 1 ? 0 : 255;

          // Apply the pixel value to the RGB pixel values
          ppm_data.PPMBody.pixel_data[index].r =
              ppm_data.PPMBody.pixel_data[index].g =
                  ppm_data.PPMBody.pixel_data[index].b = value_rgb;

          break;
        case '2':
          /* ----- Portable GrayMap, PGM, ASCII -----*/
        case '5':
          /* ----- Portable GrayMap, PGM, Binary -----*/
          const unsigned char value_p2;
          int result_pixel_p2_p5 = fscanf(ppm_file, "%d", &value_p2);

          if (result_pixel_p2_p5 != 1) {
            printf("P2 Body: Invalid pixel data (must be integers)!\n");
            return 1;
          }

          // Apply the pixel value to the RGB pixel values
          ppm_data.PPMBody.pixel_data[index].r =
              ppm_data.PPMBody.pixel_data[index].g =
                  ppm_data.PPMBody.pixel_data[index].b = value_p2;

          break;
        case '3':
          /* ----- Portable PixMap, PPM, ASCII -----*/
          int result_pixel_p3 = fscanf(ppm_file, "%d %d %d",
                                       &ppm_data.PPMBody.pixel_data[index].r,
                                       &ppm_data.PPMBody.pixel_data[index].g,
                                       &ppm_data.PPMBody.pixel_data[index].b);

          if (result_pixel_p3 != 3) {
            printf("P3 Body: Invalid pixel data (must be integers)!\n");
            return 1;
          }

          break;
        case '6':
          /* ----- Portable PixMap, PPM, Binary -----*/
          if (fread(&ppm_data.PPMBody.pixel_data[index], sizeof(Pixel), 1,
                    ppm_file) != 1) {
            printf("P6 Body: Error reading pixel data!\n");
            return 1;
          }

          break;
        default:
          // default
          break;
      }
    }
  }

  fclose(ppm_file);

  return 0;
}

const unsigned int get_width() { return ppm_data.PPMHeader.width; }
const unsigned int get_height() { return ppm_data.PPMHeader.height; }

Pixel* get_pixel_data() { return ppm_data.PPMBody.pixel_data; }