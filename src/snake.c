#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

Block pop(Body *body) {
  if (body->len) {
    body->len--;
    Block first = body->blocks[body->front];
    body->front = (body->front + 1) % body->capacity;
    return first;
  } else {
    fprintf(stderr, "no elements to deque\n");
    // TODO: i'm missing the None type from rust
    // return NULL;
    // exit(1);
  }
}

void push(Body *body, Block block) {
  if (body->len >= body->capacity) {
    int new_capacity = body->capacity ? body->capacity * 2 : 8;
    Block *new_blocks = malloc(new_capacity * sizeof(Block));
    if (new_blocks == NULL) {
      fprintf(stderr, "failed to allocate memory\n");
      exit(1);
    }

    // copy over to new memory
    int count = 0;
    for (int i = body->front; i < body->rear; i = (i + 1) % body->capacity) {
      new_blocks[count++] = body->blocks[i];
    }
    int current = body->front;
    for (int i = 0; i < body->len; i++) {
      Block block = body->blocks[current];
      new_blocks[i] = block;
      current = (current + 1) % body->capacity;
    }

    // free old array
    Block *old_blocks = body->blocks;
    body->front = 0;
    body->rear = body->len;
    body->blocks = new_blocks;
    body->capacity = new_capacity;
    free(old_blocks);
  }
  body->blocks[body->rear] = block;
  body->rear = (body->rear + 1) % body->capacity;
  body->len++;
};

void printBodyBlocks(Body *body) {
  int current = body->front;
  for (int i = 0; i < body->len; i++) {
    current = (current + 1) % body->capacity;
    Block block = body->blocks[i];
    printf("block[%d]: x: %d, y: %d\n", i, block.x, block.y);
  }
}

Block getNextBlock(Block last_block, Direction dir) {
  Direction new_dir;
  switch (dir) {
  case Up:
    new_dir = Down;
    break;
  case Right:
    new_dir = Left;
    break;
  case Down:
    new_dir = Up;
    break;
  case Left:
    new_dir = Right;
    break;
  }

  if (new_dir == Right) {
    last_block.x++;
  } else if (new_dir == Left) {
    last_block.x--;
  } else if (new_dir == Up) {
    last_block.y--;
  } else if (new_dir == Down) {
    last_block.y++;
  }
  return last_block;
}

void printBody(Body *body) {
  printf("len: %d, capacity: %d\n", body->len, body->capacity);
  printf("front: %d, rear: %d\n", body->front, body->rear);
  printBodyBlocks(body);
}

void updateSnake(Snake *snake, Direction dir) {
  Block prev_head = snake->head;
  if (snake->body.len > 0) {
    printf("------ start update --------\n");
    printf("before: x: %d, y: %d\n", snake->head.x, snake->head.y);
    printf("prev_head: x: %d, y: %d\n", prev_head.x, prev_head.y);
  }
  if (dir == Right) {
    snake->head.x++;
  } else if (dir == Left) {
    snake->head.x--;
  } else if (dir == Up) {
    snake->head.y--;
  } else if (dir == Down) {
    snake->head.y++;
  }
  if (snake->body.len > 0) {
    printf("after: x: %d, y: %d\n", snake->head.x, snake->head.y);
  }

  // TODO: only call if len(blocks) > 0
  // len of circular queue?  = rear + ((len - front) % SIZE) + 1
  if (snake->body.len > 0) {
    pop(&snake->body);
    push(&snake->body, prev_head);
    printBody(&snake->body);
    printf("------ end update --------\n");
  }
};

void DrawSnake(Snake *snake) {
  DrawRectangle(snake->head.x * snake->width, snake->head.y * snake->height,
                snake->width, snake->height, RED);

  int current = snake->body.front;
  for (int i = 0; i < snake->body.len; i++) {
    Block block = snake->body.blocks[current];
    DrawRectangle(block.x * snake->width, block.y * snake->height, snake->width,
                  snake->height, RED);
    current = (current + 1) % snake->body.capacity;
  }
}
