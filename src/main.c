#include <stdlib.h>
#include <unistd.h>

#include "raylib/raylib.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif /* ifdef PLATFORM_WEB */

#define GRID_W 20.0f
#define GRID_H 20.0f
#define SLEEP_DURATION 62500

#define RAND_RANGE(max) (rand() % max)

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int NUM_GRIDS_X = SCREEN_WIDTH / GRID_W;
const int NUM_GRIDS_Y = SCREEN_HEIGHT / GRID_H;

enum Direction { Up, Right, Down, Left };

static Vector2 snake_head = {0, 0};
static Vector2 food_pos = {NUM_GRIDS_X / 2, NUM_GRIDS_Y / 2};
static enum Direction current_dir = Right;

Vector2 GetRandomVector();
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

Vector2 GetRandomVector() {
  return (Vector2){.x = rand() % NUM_GRIDS_X, .y = rand() % NUM_GRIDS_Y};
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

  if (snake_head.x >= NUM_GRIDS_X)
    snake_head.x = 0;
  else if (snake_head.x < 0)
    snake_head.x = NUM_GRIDS_X;

  if (snake_head.y >= NUM_GRIDS_Y)
    snake_head.y = 0;
  else if (snake_head.y < 0)
    snake_head.y = NUM_GRIDS_Y;

  if (current_dir == Right) {
    snake_head.x++;
  } else if (current_dir == Left) {
    snake_head.x--;
  } else if (current_dir == Up) {
    snake_head.y--;
  } else if (current_dir == Down) {
    snake_head.y++;
  }

  if (snake_head.x == food_pos.x && snake_head.y == food_pos.y) {
    // TODO: grow the snake, update the point
    food_pos = GetRandomVector();
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

    DrawRectangle(snake_head.x * GRID_W, snake_head.y * GRID_H, GRID_W, GRID_H,
                  RED);
    DrawCircle((food_pos.x * GRID_W) + (GRID_W / 2.0f),
               (food_pos.y * GRID_H) + (GRID_H / 2.0f), GRID_W / 2.0, YELLOW);
  } // EndDrawing

  EndDrawing();
  usleep(SLEEP_DURATION);
}
