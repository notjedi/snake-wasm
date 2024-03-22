#ifndef GAME_H
#define GAME_H

#include "snake.h"

typedef struct Game {
  int score;
  Direction dir;
  bool game_over;
  Snake snake;
  Vector2 food_pos;
} Game;

Vector2 get_random_vector(int max_x, int max_y);
Game init_game(int grid_w, int grid_h, int max_w, int max_h);

#endif // GAME_H
