#ifndef GAME_H
#define GAME_H

#include "raylib/raylib.h"
#include <stdbool.h>

#include "snake.h"

typedef struct Game {
  Snake snake;      // 48 bytes
  Vector2 food_pos; // 8 bytes
  Direction dir;    // 4 bytes
  int score;        // 4 bytes
  bool game_over;   // 1 byte (8 bytes with padding)
} Game;             // 72 bytes

Vector2 get_random_vector(int max_x, int max_y);
Game init_game(int grid_w, int grid_h, int max_w, int max_h);

#endif // GAME_H
