#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#define INIT_BODY                                                              \
  (Body) { .len = 0, .capacity = 0, .front = 0, .rear = 0, .blocks = NULL }

#define INIT_SNAKE(grid_w, grid_h, max_w, max_h)                               \
  ((Snake){.head = (Block){0, 0},                                              \
           .body = INIT_BODY,                                                  \
           .width = grid_w,                                                    \
           .height = grid_h,                                                   \
           .max_x = max_w,                                                     \
           .max_y = max_h})

typedef struct Block {
  int x;
  int y;
} Block;

typedef struct Body {
  int len;
  int capacity;
  int front;
  int rear;
  Block *blocks;
} Body;

typedef struct Snake {
  Block head;
  Body body;
  int width;
  int height;
  int max_x;
  int max_y;
} Snake;

typedef enum { Up, Right, Down, Left } Direction;

Block *body_pop(Body *body);
void body_push(Body *body, Block block);

bool is_point_in_snake_body(Snake *snake, int x, int y);
bool snake_update(Snake *snake, Direction dir);
void snake_draw(Snake *snake);

#endif // SNAKE_H
