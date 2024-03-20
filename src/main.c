#include <stddef.h>
#include <stdio.h>

#include "raylib/raylib.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif /* ifdef PLATFORM_WEB */

#define MSG_STR "Hi, I'm going to build a snake game with raylib and wasm"
#define GRID_W 20.0f
#define GRID_H 20.0f

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const char *MSG = MSG_STR;
const size_t MSG_LEN = sizeof(MSG_STR) - 1;

static Rectangle snake_head = {0.0f, 0.0f, GRID_W, GRID_H};

void UpdateDrawFrame();

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");

#ifdef PLATFORM_WEB
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
  if (IsKeyDown(KEY_RIGHT)) {
    snake_head.x += GRID_W;
  } else if (IsKeyDown(KEY_LEFT)) {
    snake_head.x -= GRID_W;
  } else if (IsKeyDown(KEY_UP)) {
    snake_head.y -= GRID_H;
  } else if (IsKeyDown(KEY_DOWN)) {
    snake_head.y += GRID_H;
  }

  if (snake_head.x > SCREEN_WIDTH)
    snake_head.x = 0;
  else if (snake_head.x < 0)
    snake_head.x = SCREEN_WIDTH;

  if (snake_head.y > SCREEN_HEIGHT)
    snake_head.y = 0;
  else if (snake_head.y < 0)
    snake_head.y = SCREEN_HEIGHT;

  // Draw;
  BeginDrawing();

  { // BeginDrawing
    ClearBackground(RAYWHITE);
    for (int i = 0; i < SCREEN_WIDTH / GRID_W; i++) {
      DrawLineV((Vector2){i * GRID_W, 0.0f},
                (Vector2){i * GRID_W, SCREEN_HEIGHT}, LIGHTGRAY);
      for (int j = 0; j < SCREEN_HEIGHT / GRID_H; j++) {
        DrawLineV((Vector2){0.0f, j * GRID_H},
                  (Vector2){SCREEN_WIDTH, j * GRID_H}, LIGHTGRAY);
      }
    }

    DrawRectangleRec(snake_head, RED);
  } // EndDrawing

  EndDrawing();
}
