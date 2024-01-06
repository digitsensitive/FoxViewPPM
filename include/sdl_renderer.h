#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>

#include "ppm.h"
// SDLRenderer is a project-specific alias of the SDL_Renderer
typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} SDLRenderer;

// WindowSettings holds relevant configurations for the SDL_Window
typedef struct {
  const char *title;
  int width;
  int height;
  Uint32 flags;
} WindowSettings;

int initialize_renderer(SDLRenderer *self, const char *window_title,
                        const int window_width, const int window_height,
                        Uint32 flags);

void draw(SDLRenderer *self);
void terminate_renderer(SDLRenderer *self);