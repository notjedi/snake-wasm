#include <unistd.h>

#include "raylib/raylib.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif /* ifdef PLATFORM_WEB */

#define GRID_W 20.0f
#define GRID_H 20.0f
#define SLEEP_DURATION 62500

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

enum Direction { Up, Right, Down, Left };

static Rectangle snake_head = {0.0f, 0.0f, GRID_W, GRID_H};
static enum Direction current_dir = Right;

void UpdateDrawFrame();

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");

#ifdef PLATFORM_WEB
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else /* ifdef PLATFORM_WEB */
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();
  return 0;
}

void UpdateDrawFrame() {
  // Update;
  if (IsKeyDown(KEY_RIGHT)) {
    current_dir = Right;
  } else if (IsKeyDown(KEY_LEFT)) {
    current_dir = Left;
  } else if (IsKeyDown(KEY_UP)) {
    current_dir = Up;
  } else if (IsKeyDown(KEY_DOWN)) {
    current_dir = Down;
  }

  if (snake_head.x >= SCREEN_WIDTH)
    snake_head.x = 0;
  else if (snake_head.x < 0)
    snake_head.x = SCREEN_WIDTH - GRID_W;

  if (snake_head.y >= SCREEN_HEIGHT)
    snake_head.y = 0;
  else if (snake_head.y < 0)
    snake_head.y = SCREEN_HEIGHT - GRID_H;

  if (current_dir == Right) {
    snake_head.x += GRID_W;
  } else if (current_dir == Left) {
    snake_head.x -= GRID_W;
  } else if (current_dir == Up) {
    snake_head.y -= GRID_H;
  } else if (current_dir == Down) {
    snake_head.y += GRID_H;
  }

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
  usleep(SLEEP_DURATION);
}
