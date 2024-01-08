#include <stdio.h>

#include "ppm.h"
#include "sdl_engine.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: <ppm-viewer> <image.extension>\n");
    return -1;
  }

  int is_ppm_file_valid = read_ppm_file(argv[1]);

  if (is_ppm_file_valid) {
    printf("The *.ppm file is invalid.\n");
    return -1;
  }

  int result = initialize_engine();

  if (result != 0) {
    return result;
  }

  int done = 0;
  SDL_Event event;

  while (!done) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT:
          done = 1;
          break;
        case SDL_EVENT_KEY_DOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            done = 1;
          }
          break;
        default:
          break;
      }
    }

    run();
  }

  terminate_engine();

  return 0;
}