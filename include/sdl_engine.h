#pragma once

#include "ppm.h"
#include "sdl_renderer.h"

typedef struct {
  char is_running;
  CustomRenderer renderer;
  SDL_Event event;
} SDLEngine;

int initialize_engine(SDLEngine* engine, const char* title);
void run(SDLEngine* engine);
void process_input(SDLEngine* engine);
void terminate_engine(SDLEngine* engine);