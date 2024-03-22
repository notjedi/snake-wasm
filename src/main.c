#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif /* ifdef PLATFORM_WEB */

#include "snake.h"

#define GRID_W 20.0f
#define GRID_H 20.0f
#define SLEEP_DURATION 62500

#define RAND_RANGE(max) (rand() % max)

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int NUM_GRIDS_X = SCREEN_WIDTH / GRID_W;
const int NUM_GRIDS_Y = SCREEN_HEIGHT / GRID_H;

static int score = 0;
static Direction dir = Right;
static Vector2 foodPos = {NUM_GRIDS_X / 2, NUM_GRIDS_Y / 2};
static Snake snake = (Snake){.head = (Block){0, 0},
                             .body = INIT_BODY,
                             .width = GRID_W,
                             .height = GRID_H};

Vector2 GetRandomVector();
void UpdateDrawFrame();

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");

#ifdef PLATFORM_WEB
  // TODO: try passing args to UpdateDrawFrame using
  // emscripten_set_main_loop_arg
  emscripten_set_main_loop(UpdateDrawFrame, 10, 1);
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
    dir = Right;
  } else if (IsKeyDown(KEY_LEFT)) {
    dir = Left;
  } else if (IsKeyDown(KEY_UP)) {
    dir = Up;
  } else if (IsKeyDown(KEY_DOWN)) {
    dir = Down;
  }

  Block last_block;
  if (snake.body.len > 0) {
    last_block = snake.body.blocks[snake.body.rear - 1];
  } else {
    last_block = snake.head;
  }

  updateSnake(&snake, dir);
  if (snake.head.x >= NUM_GRIDS_X)
    snake.head.x = 0;
  else if (snake.head.x < 0)
    snake.head.x = NUM_GRIDS_X;

  if (snake.head.y >= NUM_GRIDS_Y)
    snake.head.y = 0;
  else if (snake.head.y < 0)
    snake.head.y = NUM_GRIDS_Y;

  if (snake.head.x == foodPos.x && snake.head.y == foodPos.y) {
    score++;
    foodPos = GetRandomVector();
    push(&snake.body, last_block);
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

    // Draw snake
    DrawSnake(&snake);

    // Draw food
    DrawCircle((foodPos.x * GRID_W) + (GRID_W / 2),
               (foodPos.y * GRID_H) + (GRID_H / 2), (GRID_W / 2.0) - 1.0f,
               YELLOW);
  } // EndDrawing

  EndDrawing();
}
