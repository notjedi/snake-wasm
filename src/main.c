#include "raylib/raylib.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif /* ifdef PLATFORM_WEB */

#include "game.h"
#include "snake.h"

#define GRID_W 20.0f
#define GRID_H 20.0f
#define FONT_SIZE 36
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define SLEEP_DURATION 62500
#define GAME_OVER "GAME OVER"

const int NUM_GRIDS_X = SCREEN_WIDTH / GRID_W;
const int NUM_GRIDS_Y = SCREEN_HEIGHT / GRID_H;

#define RAND_RANGE(max) (rand() % max)

void update_draw_frame(void *arg);

Vector2 center_text(Vector2 screen_size, Vector2 text_size) {
  return (Vector2){(screen_size.x / 2) - (text_size.x / 2),
                   (screen_size.y / 2) - (text_size.y / 2)};
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake babu");
  Game game = init_game(GRID_W, GRID_H, NUM_GRIDS_X, NUM_GRIDS_Y);

#ifdef PLATFORM_WEB
  emscripten_set_main_loop_arg(update_draw_frame, (void *)&game, 20, 1);
#else /* ifdef PLATFORM_WEB */
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();
  return 0;
}

void update_draw_frame(void *arg) {
  Game *game = (Game *)arg;

  // Update;
  if (IsKeyDown(KEY_RIGHT) && game->dir != Left) {
    game->dir = Right;
  } else if (IsKeyDown(KEY_LEFT) && game->dir != Right) {
    game->dir = Left;
  } else if (IsKeyDown(KEY_UP) && game->dir != Down) {
    game->dir = Up;
  } else if (IsKeyDown(KEY_DOWN) && game->dir != Up) {
    game->dir = Down;
  }

  Block last_block;
  if (game->snake.body.len > 0) {
    last_block = game->snake.body.blocks[game->snake.body.rear - 1];
  } else {
    last_block = game->snake.head;
  }

  if (game->game_over) {
    {
      BeginDrawing();
      Font default_font = GetFontDefault();
      Vector2 text_size =
          MeasureTextEx(default_font, GAME_OVER, FONT_SIZE, 1.0f);
      Vector2 text_pos =
          center_text((Vector2){SCREEN_WIDTH, SCREEN_HEIGHT}, text_size);
      DrawTextEx(default_font, GAME_OVER, text_pos, FONT_SIZE, 1.0f, VIOLET);
      EndDrawing();
      // https://github.com/emscripten-core/emscripten/issues/2766
      emscripten_cancel_main_loop();
      return;
    }
  }
  game->game_over = snake_update(&game->snake, game->dir);

  // Adjust snake head position to wrap around the screen
  game->snake.head.x = (game->snake.head.x + NUM_GRIDS_X) % NUM_GRIDS_X;
  game->snake.head.y = (game->snake.head.y + NUM_GRIDS_Y) % NUM_GRIDS_Y;

  if (game->snake.head.x == game->food_pos.x &&
      game->snake.head.y == game->food_pos.y) {
    game->score++;
    body_push(&game->snake.body, last_block);
    Vector2 food_pos = get_random_vector(NUM_GRIDS_X, NUM_GRIDS_Y);
    while (is_point_in_snake_body(&game->snake, food_pos.x, food_pos.y))
      food_pos = get_random_vector(NUM_GRIDS_X, NUM_GRIDS_Y);
    game->food_pos = food_pos;
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
    snake_draw(&game->snake);

    // Draw food
    DrawCircle((game->food_pos.x * GRID_W) + (GRID_W / 2),
               (game->food_pos.y * GRID_H) + (GRID_H / 2),
               (GRID_W / 2.0) - 1.0f, YELLOW);
  } // EndDrawing

  EndDrawing();
}
