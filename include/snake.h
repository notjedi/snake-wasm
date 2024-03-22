#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#define INIT_BODY                                                              \
  (Body) { .len = 0, .front = 0, .rear = 0, .capacity = 0, .blocks = NULL }

typedef struct Block {
  int x;
  int y;
} Block;

typedef struct Body {
  // TODO: no need for len, when capacity is hit -> rear == front
  int len;
  int rear;
  int front;
  int capacity;
  Block *blocks;
} Body;

typedef struct Snake {
  Block head;
  Body body;
  int width;
  int height;
} Snake;

typedef enum { Up, Right, Down, Left } Direction;

Block getNextBlock(Block last_block, Direction dir);

Block pop(Body *body);
void push(Body *body, Block block);

void updateSnake(Snake *snake, Direction dir);
void DrawSnake(Snake *snake);

void printBodyBlocks(Body *body);

#endif // SNAKE_H
