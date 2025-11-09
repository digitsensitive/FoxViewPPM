#include "sdl_renderer.h"

SDL_Texture *image_texture;

int initialize_renderer(CustomRenderer *renderer, const char *window_title,
                        const int window_width, const int window_height,
                        Uint32 flags) {
  renderer->window_title = window_title;
  renderer->screen_width = window_width;
  renderer->screen_height = window_height;
  renderer->render_flags = flags;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    // In the case that the SDL failed to initialize ...
    printf("SDL_Init() failed: %s\n", SDL_GetError());
    return 1;
  }

  renderer->window =
      SDL_CreateWindow(renderer->window_title, renderer->screen_width,
                       renderer->screen_height, renderer->render_flags);

  if (renderer->window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  renderer->renderer =
      SDL_CreateRenderer(renderer->window, 0);

  if (renderer->renderer == NULL) {
    // In the case that the renderer could not be made...
    printf("Could not create renderer: %s\n", SDL_GetError());
    return 1;
  }

  // Create an SDL surface from pixel data
  SDL_Surface *pixel_surface = SDL_CreateSurfaceFrom(
       renderer->screen_width, renderer->screen_height,SDL_PIXELFORMAT_RGB24,
       get_pixel_data(),get_width() * sizeof(Pixel));

  // Create a texture from the surface
  image_texture =
      SDL_CreateTextureFromSurface(renderer->renderer, pixel_surface);
  SDL_DestroySurface(pixel_surface);

  return 0;
}

void draw(CustomRenderer *renderer) {
  SDL_RenderClear(renderer->renderer);
  SDL_RenderTexture(renderer->renderer, image_texture, NULL, NULL);
  SDL_RenderPresent(renderer->renderer);
}

void terminate_renderer(CustomRenderer *renderer) {
  free_pixel_data();
  SDL_DestroyTexture(image_texture);
  SDL_DestroyRenderer(renderer->renderer);
  SDL_DestroyWindow(renderer->window);
}