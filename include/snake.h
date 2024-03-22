#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#define INIT_BODY                                                              \
  (Body) { .len = 0, .capacity = 0, .front = 0, .rear = 0, .blocks = NULL }

typedef struct Block {
  int x;
  int y;
} Block;

typedef struct Body {
  // TODO: no need for len, when capacity is hit -> rear == front
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

Block body_pop(Body *body);
void body_push(Body *body, Block block);

bool snake_update(Snake *snake, Direction dir);
void snake_draw(Snake *snake);

#endif // SNAKE_H
