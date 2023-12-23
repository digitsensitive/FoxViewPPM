#include <stdio.h>

#include "SDL3/SDL.h"

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  // Create an application window with the following settings:
  SDL_Window* window = SDL_CreateWindow("An SDL2 window",  // window title
                                        640,               // width, in pixels
                                        480,               // height, in pixels
                                        SDL_WINDOW_OPENGL  // flags - see below
  );

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Delay(10000);

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}