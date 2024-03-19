#include <stddef.h>

#include "raylib/raylib.h"

#define MSG_STR "Hi, I'm going to build a snake game with raylib and wasm"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char *MSG = MSG_STR;
const size_t MSG_LEN = sizeof(MSG_STR) - 1;

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");
  // SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update;

    // Draw;
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Hi, I'm going to build a snake game with raylib and wasm", 170,
             360, 20, MAGENTA);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
