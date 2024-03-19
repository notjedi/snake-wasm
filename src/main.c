#include <stddef.h>
#include <stdio.h>

#include "raylib/raylib.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif /* ifdef PLATFORM_WEB */

#define MSG_STR "Hi, I'm going to build a snake game with raylib and wasm"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char *MSG = MSG_STR;
const size_t MSG_LEN = sizeof(MSG_STR) - 1;

void UpdateDrawFrame();

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");

#ifdef PLATFORM_WEB
  printf("Hi, you selected PLATFORM_WEB\n");
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif /* ifdef PLATFORM_WEB */

  CloseWindow();
  return 0;
}

void UpdateDrawFrame() {
  // Update;

  // Draw;
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawText("Hi, I'm going to build a snake game with raylib and wasm", 170, 360,
           20, MAGENTA);

  EndDrawing();
}
