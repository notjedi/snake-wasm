#include "snake.h"
#include <string.h>

Block *body_pop(Body *body) {
  if (body->len) {
    body->len--;
    Block *first = &body->blocks[body->front];
    body->front = (body->front + 1) % body->capacity;
    return first;
  } else {
    fprintf(stderr, "no elements to deque\n");
    return NULL;
  }
}

void body_push(Body *body, Block block) {
  if (body->len >= body->capacity) {
    int new_capacity = body->capacity ? body->capacity * 2 : 2;
    Block *new_blocks = malloc(new_capacity * sizeof(Block));
    if (new_blocks == NULL) {
      fprintf(stderr, "failed to allocate memory\n");
      exit(1);
    }

    // copy over to new memory
    if (body->len > 0) {
      int start = body->front;
      int end = (body->front + body->len - 1) % body->capacity;
      if (end >= start) {
        int num_elements = end - start + 1;
        memcpy(new_blocks, &body->blocks[start], num_elements * sizeof(Block));
      } else {
        int num_elements_before_wrap = body->capacity - start;
        int num_elements_after_wrap = end + 1;
        memcpy(new_blocks, &body->blocks[start],
               num_elements_before_wrap * sizeof(Block));
        memcpy(new_blocks + num_elements_before_wrap, body->blocks,
               num_elements_after_wrap * sizeof(Block));
      }
    }

    // free old array
    free(body->blocks);
    body->front = 0;
    body->rear = body->len;
    body->blocks = new_blocks;
    body->capacity = new_capacity;
  }

  body->blocks[body->rear] = block;
  body->rear = (body->rear + 1) % body->capacity;
  body->len++;
};

bool snake_update(Snake *snake, Direction dir) {
  Block prev_head = snake->head;
  switch (dir) {
  case Up:
    snake->head.y--;
    break;
  case Right:
    snake->head.x++;
    break;
  case Down:
    snake->head.y++;
    break;
  case Left:
    snake->head.x--;
    break;
  }

  int current = snake->body.front;
  for (int i = 0; i < snake->body.len; i++) {
    Block block = snake->body.blocks[current];
    if (block.x == snake->head.x && block.y == snake->head.y) {
      return true;
    }
  }

  // len of circular queue?  = rear + ((len - front) % SIZE) + 1
  if (snake->body.len > 0) {
    body_pop(&snake->body);
    body_push(&snake->body, prev_head);
  }
  return false;
};

void snake_draw(Snake *snake) {
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
