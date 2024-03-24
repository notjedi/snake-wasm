#include "game.h"
#include "snake.h"

Vector2 get_random_vector(int max_x, int max_y) {
  return (Vector2){.x = rand() % max_x, .y = rand() % max_y};
}

Game init_game(int grid_w, int grid_h, int max_w, int max_h, int fps) {
  return (Game){
      .score = 0,
      .dir = Right,
      .game_over = false,
      .snake = INIT_SNAKE(grid_w, grid_h, max_w, max_h),
      .fps = fps,
      .food_pos = get_random_vector(max_w, max_h),
  };
}
