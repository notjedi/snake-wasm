#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
static Snake snake = (Snake){.x = 0, .y = 0, .width = GRID_W, .height = GRID_H};
static Vector2 foodPos = {NUM_GRIDS_X / 2, NUM_GRIDS_Y / 2};

static Rectangle foodSourceRec;
static Rectangle foodDestRec;
static Vector2 origin;
static Texture2D scarfy;

Vector2 GetRandomVector();
void UpdateDrawFrame();

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");
  scarfy = LoadTexture("resources/scarfy.png");

  int foodWidth = scarfy.width / 6;
  int foodHeight = scarfy.height;
  origin = (Vector2){(float)foodWidth, (float)foodHeight};
  foodSourceRec = (Rectangle){0.0f, 0.0f, (float)foodWidth, (float)foodHeight};
  foodDestRec =
      (Rectangle){foodPos.x * GRID_W, foodPos.y * GRID_H, GRID_W, GRID_H};

  printf("scarfy:= w: %d, h: %d, id: %u\n", scarfy.width, scarfy.height,
         scarfy.id);
  printf("foodWidth: %d, foodHeight: %d\n", foodWidth, foodHeight);
  printf("source:= x: %f, y: %f, w: %f, h: %f\n", foodSourceRec.x,
         foodSourceRec.y, foodSourceRec.width, foodSourceRec.height);

#ifdef PLATFORM_WEB
  // TODO: try passing args to UpdateDrawFrame using
  // emscripten_set_main_loop_arg
  emscripten_set_main_loop(UpdateDrawFrame, 20, 1);
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

  updateSnake(&snake, dir);

  if (snake.x >= NUM_GRIDS_X)
    snake.x = 0;
  else if (snake.x < 0)
    snake.x = NUM_GRIDS_X;

  if (snake.y >= NUM_GRIDS_Y)
    snake.y = 0;
  else if (snake.y < 0)
    snake.y = NUM_GRIDS_Y;

  if (snake.x == foodPos.x && snake.y == foodPos.y) {
    score++;
    foodPos = GetRandomVector();
    foodDestRec = (Rectangle){.x = foodPos.x * GRID_W,
                              .y = foodPos.y * GRID_H,
                              .width = GRID_W,
                              .height = GRID_H};
    printf("dest:= x: %f, y: %f, w: %f, h: %f\n", foodDestRec.x, foodDestRec.y,
           foodDestRec.width, foodDestRec.height);
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

    DrawRectangle(snake.x * GRID_W, snake.y * GRID_H, GRID_W, GRID_H, RED);
    DrawTexturePro(scarfy, foodSourceRec, foodDestRec, origin, 0.0, VIOLET);
    // DrawCircle((foodPos.x * GRID_W) + (GRID_W / 2.0f),
    //            (foodPos.y * GRID_H) + (GRID_H / 2.0f), GRID_W / 2.0, YELLOW);
  } // EndDrawing

  EndDrawing();
  // usleep(SLEEP_DURATION);
}
