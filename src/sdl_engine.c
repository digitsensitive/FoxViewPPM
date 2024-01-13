#include "sdl_engine.h"

int initialize_engine(SDLEngine* engine, const char* title) {
  engine->is_running = 1;

  int result = initialize_renderer(&engine->renderer, title, get_width(),
                                   get_height(), SDL_WINDOW_OPENGL);

  if (result != 0) {
    printf("Error initializing renderer: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

void run(SDLEngine* engine) {
  while (engine->is_running) {
    process_input(engine);
    draw(&engine->renderer);
  }
}

void process_input(SDLEngine* engine) {
  while (SDL_PollEvent(&engine->event) != 0) {
    switch (engine->event.type) {
      case SDL_EVENT_QUIT:
        engine->is_running = 0;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (engine->event.key.keysym.sym == SDLK_ESCAPE) {
          engine->is_running = 0;
        }
        break;
      default:
        break;
    }
  }
}

void terminate_engine(SDLEngine* engine) {
  terminate_renderer(&engine->renderer);
  SDL_Quit();
}