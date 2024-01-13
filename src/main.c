#include <stdio.h>

#include "ppm.h"
#include "sdl_engine.h"

SDLEngine engine;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: <ppm-viewer> <image.extension>\n");
    return -1;
  }

  int is_file_valid = read_ppm_file(argv[1]);

  if (!is_file_valid) {
    printf("The *.ppm file is invalid.\n");
    return -1;
  }

  int init_succeeded = initialize_engine(&engine, argv[1]);

  if (init_succeeded) {
    run(&engine);
  }

  terminate_engine(&engine);

  return 0;
}