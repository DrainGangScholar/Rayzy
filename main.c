#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define WIDTH 1280
#define HEIGHT 720
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
int *frame_buffer;
static bool running = true;

bool update() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_EVENT_QUIT) {
    return false;
  }
  if (event.type == SDL_EVENT_KEY_UP && event.key.key == SDLK_ESCAPE) {
    return false;
  }
  char *pix;
  int pitch;
  SDL_LockTexture(texture, NULL, (void **)&pix, &pitch);
  for (int i = 0, sp = 0, dp = 0; i < HEIGHT; i++, dp += WIDTH, sp += pitch)
    memcpy(pix + sp, frame_buffer + dp, WIDTH * 4);
  SDL_UnlockTexture(texture);
  SDL_RenderTexture(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(1);
  return true;
}

void render(Uint64 ticks) {
  for (int i = 0, c = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++, c++) {
      frame_buffer[c] = (int)(i * i + j * j + ticks) | 0xff0000ff;
    }
  }
}
void loop() {
  if (!update()) {
  } else {
    render(SDL_GetTicks());
  }
}
int main() {

  frame_buffer = malloc(sizeof(int) * WIDTH * HEIGHT);
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    fprintf(stderr, "Failed to initialize SDL.");
    return -1;
  };
  window = SDL_CreateWindow("Test SDL3", WIDTH, HEIGHT, 0);
  if (window == NULL) {
    fprintf(stderr, "Failed to create an SDL Window.");
    return -1;
  }
  renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == NULL) {
    fprintf(stderr, "Failed to create an SDL Renderer.");
    return -1;
  }
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
  if (texture == NULL) {
    fprintf(stderr, "Failed to create an SDL Texture.");
    return -1;
  }
  while (running) {
    loop();
  }
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}
