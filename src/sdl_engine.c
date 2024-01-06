#include "sdl_engine.h"

// Declare instance of struct SDLRenderer
SDLRenderer renderer;

int initialize_engine() {
  int result = initialize_renderer(&renderer, "My Engine", get_width(),
                                   get_height(), SDL_WINDOW_OPENGL);

  if (result != 0) {
    printf("Error initializing renderer: %s\n", SDL_GetError());
    return 1;
  }

  return 0;
}

void run() { draw(&renderer); }

void terminate_engine() {
  terminate_renderer(&renderer);
  SDL_Quit();
}