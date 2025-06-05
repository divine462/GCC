
#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define CELL_SIZE 20
#define WIDTH 800
#define HEIGHT 600
#define COLS (WIDTH / CELL_SIZE)
#define ROWS (HEIGHT / CELL_SIZE)
#define MAX_LENGTH 100

typedef struct {
    int x, y;
} Position;

typedef enum {
    UP, DOWN, LEFT, RIGHT
} Direction;

// === Variables globales ===
Position snake[MAX_LENGTH];
int snakeLength;
Position fruit;
Direction direction;
bool gameOver;
int score;
int frameCounter = 0; // Pour ralentir le serpent

// === Fonctions ===
void InitGame();
void UpdateGame();
void DrawGame();
bool CheckCollisions();
void GenerateFruit();
void ResetGame();

void GenerateFruit() {
    bool validPosition = false;
    while (!validPosition) {
        fruit.x = rand() % (GetScreenWidth() / CELL_SIZE);
        fruit.y = rand() % (GetScreenHeight() / CELL_SIZE);
        validPosition = true;
        for (int i = 0; i < snakeLength; i++) {
            if (snake[i].x == fruit.x && snake[i].y == fruit.y) {
                validPosition = false;
                break;
            }
        }
    }
}

void ResetGame() {
    snakeLength = 1;
    snake[0].x = (GetScreenWidth() / CELL_SIZE) / 2;
    snake[0].y = (GetScreenHeight() / CELL_SIZE) / 2;
    direction = RIGHT;
    score = 0;
    gameOver = false;
    GenerateFruit();
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "🐍 Snake - Raylib");
    SetTargetFPS(60);
    InitGame();

    while (!WindowShouldClose()) {
        if (!gameOver) {
            frameCounter++;
            if (frameCounter >= 6) { // Contrôle la vitesse de déplacement
                UpdateGame();
                frameCounter = 0;
            }
        } else if (IsKeyPressed(KEY_R)) {
            ResetGame();
        }

        DrawGame();
    }

    CloseWindow();
    return 0;
}

void InitGame() {
    snakeLength = 3;
    for (int i = 0; i < snakeLength; i++) {
        snake[i].x = COLS / 2 - i;
        snake[i].y = ROWS / 2;
    }

    direction = RIGHT;
    gameOver = false;
    score = 0;
    GenerateFruit();
}

void UpdateGame() {
    // Gestion des touches
    if (IsKeyPressed(KEY_UP) && direction != DOWN) direction = UP;
    if (IsKeyPressed(KEY_DOWN) && direction != UP) direction = DOWN;
    if (IsKeyPressed(KEY_LEFT) && direction != RIGHT) direction = LEFT;
    if (IsKeyPressed(KEY_RIGHT) && direction != LEFT) direction = RIGHT;

    // Décalage du corps
    for (int i = snakeLength; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Mise à jour de la tête
    switch (direction) {
        case UP:    snake[0].y--; break;
        case DOWN:  snake[0].y++; break;
        case LEFT:  snake[0].x--; break;
        case RIGHT: snake[0].x++; break;
    }

    // Collision
    if (CheckCollisions()) {
        gameOver = true;
        return;
    }

    // Fruit mangé
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        snakeLength++;
        score++;
        GenerateFruit();
    }
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    if (!gameOver) {
        // Dessiner le fruit
        DrawRectangle(fruit.x * CELL_SIZE, fruit.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

        // Dessiner le serpent
        for (int i = 0; i < snakeLength; i++) {
            DrawRectangle(snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
        }

        // Score
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
    } else {
        DrawText("GAME OVER", WIDTH / 2 - 100, HEIGHT / 2 - 40, 40, RED);
        DrawText(TextFormat("Score: %d", score), WIDTH / 2 - 70, HEIGHT / 2 + 10, 20, WHITE);
        DrawText("Appuie sur [R] pour rejouer", WIDTH / 2 - 110, HEIGHT / 2 + 40, 20, LIGHTGRAY);
    }

    EndDrawing();
}

bool CheckCollisions() {
    // Collision murs
    if (snake[0].x < 0 || snake[0].x >= COLS || snake[0].y < 0 || snake[0].y >= ROWS) {
        return true;
    }

    // Collision corps
    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    return false;
}


