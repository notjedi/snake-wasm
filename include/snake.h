#ifndef SNAKE_H
#define SNAKE_H

#include "raylib/raylib.h"

typedef struct Snake {
  int x;
  int y;
  int width;
  int height;
} Snake;

typedef enum { Up, Right, Down, Left } Direction;

void updateSnake(Snake *snake, Direction dir);
void DrawSnake(Snake *snake);

#endif // SNAKE_H
