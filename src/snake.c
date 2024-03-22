#include "snake.h"

void updateSnake(Snake *snake, Direction dir) {
  if (dir == Right) {
    snake->x++;
  } else if (dir == Left) {
    snake->x--;
  } else if (dir == Up) {
    snake->y--;
  } else if (dir == Down) {
    snake->y++;
  }
};

void DrawSnake(Snake *snake) {
  DrawRectangle(snake->x * snake->width, snake->y * snake->height, snake->width,
                snake->height, RED);
}
