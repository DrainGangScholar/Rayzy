#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  int width = 320, height = 240;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Failed to initialize SDL.");
  };
  SDL_Window *window;
  window = SDL_CreateWindow("Test SDL3", width, height, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    fprintf(stderr, "Failed to create a SDL Window.");
  }
  SDL_Renderer *renderer;
  renderer = SDL_CreateRenderer(window, NULL);
  SDL_Texture *texture;
  SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                    SDL_TEXTUREACCESS_TARGET, width / 2, height / 2);
  int running = 1;
  SDL_Event event;
  SDL_FRect r;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = 0;
      }

      SDL_SetRenderTarget(renderer, texture);
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
      SDL_RenderClear(renderer);
      SDL_RenderRect(renderer, &r);
      SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
      SDL_RenderFillRect(renderer, &r);
      SDL_SetRenderTarget(renderer, NULL);
      SDL_RenderTexture(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
  }
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}
