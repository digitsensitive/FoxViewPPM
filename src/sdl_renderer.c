#include "sdl_renderer.h"

WindowSettings window;
SDL_Texture *image_texture;

int initialize_renderer(SDLRenderer *self, const char *window_title,
                        const int window_width, const int window_height,
                        Uint32 flags) {
  window.title = window_title;
  window.width = window_width;
  window.height = window_height;
  window.flags = flags;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    // In the case that the SDL failed to initialize ...
    printf("SDL_Init() failed: %s\n", SDL_GetError());
    return 1;
  }

  self->window =
      SDL_CreateWindow(window.title, window.width, window.height, window.flags);

  if (self->window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  self->renderer = SDL_CreateRenderer(
      self->window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (self->renderer == NULL) {
    // In the case that the renderer could not be made...
    printf("Could not create renderer: %s\n", SDL_GetError());
    return 1;
  }

  // Create an SDL surface from pixel data
  SDL_Surface *pixel_surface =
      SDL_CreateSurfaceFrom(get_pixel_data(), window.width, window.height,
                            get_width() * sizeof(Pixel), SDL_PIXELFORMAT_RGB24);

  // Create a texture from the surface
  image_texture = SDL_CreateTextureFromSurface(self->renderer, pixel_surface);
  SDL_DestroySurface(pixel_surface);

  return 0;
}

void draw(SDLRenderer *self) {
  SDL_RenderClear(self->renderer);
  SDL_RenderTexture(self->renderer, image_texture, NULL, NULL);
  SDL_RenderPresent(self->renderer);
}

void terminate_renderer(SDLRenderer *self) {
  free_pixel_data();
  SDL_DestroyTexture(image_texture);
  SDL_DestroyRenderer(self->renderer);
  SDL_DestroyWindow(self->window);
}