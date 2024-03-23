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
  int x; // 4 bytes
  int y; // 4 bytes
} Block; // 8 bytes

typedef struct Body {
  Block *blocks; // 8 bytes
  int capacity;  // 4 bytes
  int front;     // 4 bytes
  int rear;      // 4 bytes
  int len;       // 4 bytes
} Body;          // 24 bytes

typedef struct Snake {
  Body body;  // 24 bytes
  Block head; // 8 bytes
  int width;  // 4 bytes
  int height; // 4 bytes
  int max_x;  // 4 bytes
  int max_y;  // 4 bytes
} Snake;      // 48 bytes

typedef enum { Up, Right, Down, Left } Direction; // 4 bytes

Block *body_pop(Body *body);
void body_push(Body *body, Block block);

bool is_point_in_snake_body(Snake *snake, int x, int y);
bool snake_update(Snake *snake, Direction dir);
void snake_draw(Snake *snake);

#endif // SNAKE_H
