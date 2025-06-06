#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CELL_SIZE 20
#define COLS (SCREEN_WIDTH / CELL_SIZE)
#define ROWS (SCREEN_HEIGHT / CELL_SIZE)
#define MAX_LENGTH 100

typedef struct {
    int x;
    int y;
} Position;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

Position snake[MAX_LENGTH];
int snakeLength;
Position fruit;
Direction direction;
bool gameOver;
int score;

int frameCounter = 0;
int updateRate = 15;  // Plus grand = plus lent

void GenerateFruit() {
    bool valid = false;
    while (!valid) {
        fruit.x = rand() % COLS;
        fruit.y = rand() % ROWS;
        valid = true;

        for (int i = 0; i < snakeLength; i++) {
            if (snake[i].x == fruit.x && snake[i].y == fruit.y) {
                valid = false;
                break;
            }
        }
    }
}

void InitGame() {
    snakeLength = 1;
    snake[0].x = COLS / 2;
    snake[0].y = ROWS / 2;
    direction = RIGHT;
    gameOver = false;
    score = 0;
    frameCounter = 0;

    srand(time(NULL));
    GenerateFruit();
}

bool CheckCollisions() {
    if (snake[0].x < 0 || snake[0].x >= COLS || snake[0].y < 0 || snake[0].y >= ROWS) {
        return true;
    }

    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    return false;
}

void HandleInput() {
    if (IsKeyDown(KEY_UP) && direction != DOWN) direction = UP;
    else if (IsKeyDown(KEY_DOWN) && direction != UP) direction = DOWN;
    else if (IsKeyDown(KEY_LEFT) && direction != RIGHT) direction = LEFT;
    else if (IsKeyDown(KEY_RIGHT) && direction != LEFT) direction = RIGHT;
}

void UpdateGame() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case UP:    snake[0].y--; break;
        case DOWN:  snake[0].y++; break;
        case LEFT:  snake[0].x--; break;
        case RIGHT: snake[0].x++; break;
    }

    if (CheckCollisions()) {
        gameOver = true;
        return;
    }

    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        if (snakeLength < MAX_LENGTH) snakeLength++;
        score += 10;
        GenerateFruit();
    }
}

void DrawGame() {
    ClearBackground(RAYWHITE);

    for (int i = 0; i < snakeLength; i++) {
        DrawRectangle(snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGREEN);
    }

    DrawRectangle(fruit.x * CELL_SIZE, fruit.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

    if (gameOver) {
        DrawText("GAME OVER!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, MAROON);
        DrawText("Appuie sur R pour rejouer", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 30, 20, DARKGRAY);
    }
}

void ResetGame() {
    InitGame();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake avec Raylib");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (!gameOver) {
            HandleInput(); // 🔄 lire la direction à chaque frame
            frameCounter++;
            if (frameCounter >= updateRate) {
                UpdateGame();
                frameCounter = 0;
            }
        } else {
            if (IsKeyPressed(KEY_R)) {
                ResetGame();
            }
        }

        DrawGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
