#include "ppm.h"

PPMFile ppm_data;

void set_rgb_color_at(unsigned int index, const unsigned color) {
  ppm_data.Body.pixel_data[index].r = ppm_data.Body.pixel_data[index].g =
      ppm_data.Body.pixel_data[index].b = color;
}

int read_ppm_file(const char* ppm_file_path) {
  FILE* ppm_file;

  ppm_file = fopen(ppm_file_path, "rb");

  if (ppm_file == NULL) {
    printf("Memory allocation for FILE pointer failed!\n");
    return 0;
  }

  /* ------------------------- PPM Header ------------------------- */
  // File Type
  fscanf(ppm_file, "%2s", ppm_data.Header.file_type);
  ppm_data.Header.file_type[2] = '\0';  // Null-terminate the string

  if (ppm_data.Header.file_type[0] != 'P' ||
      !(ppm_data.Header.file_type[1] >= '1' &&
        ppm_data.Header.file_type[1] <= '6')) {
    printf("Invalid PPM file format!\n");
    fclose(ppm_file);
    return 0;
  }

  // Width and Height
  int result_image_size = fscanf(ppm_file, "%d %d", &ppm_data.Header.width,
                                 &ppm_data.Header.height);

  if (result_image_size != 2) {
    printf("Invalid width and/or height (must be integers)!\n");
    fclose(ppm_file);
    return 0;
  }

  // Maximum color value
  ppm_data.Header.maxval = 0;  // Default value of maxval is 0

  if (ppm_data.Header.file_type[1] == '2' ||
      ppm_data.Header.file_type[1] == '3' ||
      ppm_data.Header.file_type[1] == '5' ||
      ppm_data.Header.file_type[1] == '6') {
    int result_maxval = fscanf(ppm_file, "%d", &ppm_data.Header.maxval);

    if (result_maxval != 1 || ppm_data.Header.maxval >= 65536 ||
        ppm_data.Header.maxval <= 0) {
      printf("Invalid maxval value (must be integer and > 0 and < 65536)!\n");
      fclose(ppm_file);
      return 0;
    }
  }

  /* ------------------------- PPM Body ------------------------- */
  // Allocate memory for pixel data
  ppm_data.Body.pixel_data = (Pixel*)malloc(
      ppm_data.Header.width * ppm_data.Header.height * sizeof(Pixel));

  if (ppm_data.Body.pixel_data == NULL) {
    printf("Memory allocation for pixel data failed!\n");
    fclose(ppm_file);
    return 0;
  }

  for (int y = 0; y < ppm_data.Header.height; y++) {
    for (int x = 0; x < ppm_data.Header.width; x++) {
      unsigned int index = y * ppm_data.Header.width + x;

      switch (ppm_data.Header.file_type[1]) {
        case '1':
          /* ----- Portable BitMap, PBM, ASCII -----*/
        case '4': {
          /* ----- Portable BitMap, PBM, Binary -----*/
          // Get current pixel value, ASCII "0" or "1"
          const unsigned char value_p1;
          int result_pixel_p1_p4 = fscanf(ppm_file, "%d", &value_p1);

          if (result_pixel_p1_p4 > 1 || result_pixel_p1_p4 < 0) {
            printf("P1 Body: Invalid pixel data (must be integers)!\n");
            fclose(ppm_file);
            return 0;
          }

          // Traditionally "0" refers to white while "1" refers to black.
          const unsigned char rgb_value = value_p1 == 1 ? 0 : 255;

          // Apply the pixel value to the RGB pixel values
          set_rgb_color_at(index, rgb_value);
        } break;
        case '2':
          /* ----- Portable GrayMap, PGM, ASCII -----*/
        case '5': {
          /* ----- Portable GrayMap, PGM, Binary -----*/
          const unsigned char value_p2;
          int result_pixel_p2_p5 = fscanf(ppm_file, "%d", &value_p2);

          if (result_pixel_p2_p5 != 1) {
            printf("P2 Body: Invalid pixel data (must be integers)!\n");
            fclose(ppm_file);
            return 0;
          }

          // Apply the pixel value to the RGB pixel values
          set_rgb_color_at(index, value_p2);
        } break;
        case '3': {
          /* ----- Portable PixMap, PPM, ASCII -----*/
          int result_pixel_p3 =
              fscanf(ppm_file, "%d %d %d", &ppm_data.Body.pixel_data[index].r,
                     &ppm_data.Body.pixel_data[index].g,
                     &ppm_data.Body.pixel_data[index].b);

          if (result_pixel_p3 != 3) {
            printf("P3 Body: Invalid pixel data (must be integers)!\n");
            fclose(ppm_file);
            return 0;
          }
        } break;
        case '6':
          /* ----- Portable PixMap, PPM, Binary -----*/
          if (fread(&ppm_data.Body.pixel_data[index], sizeof(Pixel), 1,
                    ppm_file) != 1) {
            printf("P6 Body: Error reading pixel data!\n");
            fclose(ppm_file);
            return 0;
          }

          break;
        default:
          // default
          break;
      }
    }
  }

  fclose(ppm_file);

  return 1;
}

const unsigned int get_width() { return ppm_data.Header.width; }
const unsigned int get_height() { return ppm_data.Header.height; }
void free_pixel_data() { free(ppm_data.Body.pixel_data); }
Pixel* get_pixel_data() { return ppm_data.Body.pixel_data; }