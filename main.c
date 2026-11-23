#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

typedef enum {
    PLAYING,
    PAUSED,
    GAME_OVER
} gameState;

#define WIDTH 1280
#define HEIGHT 720
#define MAX_ENEMY 200
#define MAX_BULLETS 1200
#define MAX_QUEUE 100
#define MAX_TEXTURE 10

SpawnQueue queue;
Player player;
Texture2D enemyTexture[MAX_TEXTURE];
Enemy enemy[MAX_ENEMY];
Bullet bullets[MAX_BULLETS];

gameState estadoAtual = PLAYING;

Rectangle chao = { 0, 600, 1280, 120 };

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(60);

    InitWindow(WIDTH, HEIGHT, "Hello Raylib");

    SearchAndSetResourceDir("resources");

    defStPlayer(&player, WIDTH, HEIGHT);
    //loadEnemy(enemyTexture);


    inicializar(&queue);

    enqueue(&queue, ENEMY_SLIME, 1.0f);
    enqueue(&queue, ENEMY_SKELETON, 3.0f);
    enqueue(&queue, ENEMY_GHOST, 5.0f);
    enqueue(&queue, ENEMY_SLIME, 1.0f);
    enqueue(&queue, ENEMY_SKELETON, 4.0f);

    Rectangle continuePlaying = { WIDTH / 2.0f - 100, 280, 200, 50 };
    Rectangle quitGame = { WIDTH / 2.0f - 100, 360, 200, 50 };
    Rectangle resetGame = { WIDTH / 2.0f - 100, 360, 200, 50 };

    while (!WindowShouldClose())
    {

        switch (estadoAtual)
        {
        case PLAYING:
        {
            float frameTime = GetFrameTime();

            movePlayer(&player, &chao);
            moveEnemy(enemy, MAX_ENEMY, &player);
            updateEnemy(enemy, MAX_ENEMY, &player, bullets);
            updateBullet(bullets, MAX_BULLETS);
            checkBulletColl(bullets, MAX_BULLETS, enemy, MAX_ENEMY, &player);

  
            EnemiesType type;

            if (dequeue(&queue, &type, frameTime)) {
                spawnEnemy(enemy, type, MAX_ENEMY, &player, WIDTH, HEIGHT);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                Vector2 directionP = Vector2Normalize(
                    Vector2Subtract(GetMousePosition(), player.position)
                );

                spawnBullet(bullets, MAX_BULLETS, player.position,
                    directionP, BULLET_PLAYER, &player);
            }

            if (IsKeyPressed(KEY_F1))
                estadoAtual = PAUSED;

            if (player.life <= 0)
                estadoAtual = GAME_OVER;

            break;
        }

        case PAUSED:
        {
            if (CheckCollisionPointRec(GetMousePosition(), continuePlaying)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    estadoAtual = PLAYING;
            }

            if (CheckCollisionPointRec(GetMousePosition(), quitGame)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    CloseWindow();
                    return 0;
                }
            }

            if (IsKeyPressed(KEY_F1))
                estadoAtual = PLAYING;

            break;
        }

        case GAME_OVER:
        {
            if (CheckCollisionPointRec(GetMousePosition(), resetGame)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                    defStPlayer(&player, WIDTH, HEIGHT);

                    for (int i = 0; i < MAX_ENEMY; i++) {
                        enemy[i].active = false;
                    }

                    for (int i = 0; i < MAX_BULLETS; i++) {
                        bullets[i].active = false;
                    }

                    inicializar(&queue);

                    enqueue(&queue, ENEMY_SLIME, 1.0f);
                    enqueue(&queue, ENEMY_SKELETON, 3.0f);
                    enqueue(&queue, ENEMY_GHOST, 5.0f);
                    enqueue(&queue, ENEMY_SLIME, 1.0f);
                    enqueue(&queue, ENEMY_SKELETON, 4.0f);

                    estadoAtual = PLAYING;
                }
            }

            break;
        }
        }


        BeginDrawing();
        ClearBackground(BLACK);

        switch (estadoAtual)
        {
        case PLAYING:
        {
            drawPlayer(&player);
            drawEnemy(enemy, MAX_ENEMY);
            DrawRectangleRec(chao, PINK);
            drawBullet(bullets, MAX_BULLETS);

            break;
        }

        case PAUSED:
        {
            drawPlayer(&player);
            drawEnemy(enemy, MAX_ENEMY);
            DrawRectangleRec(chao, PINK);
            drawBullet(bullets, MAX_BULLETS);

            DrawRectangle(0, 0, WIDTH, HEIGHT, Fade(BLACK, 0.7f));

            DrawText("GAME PAUSED",
                WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2,
                180, 40, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), continuePlaying)) {
                DrawRectangleRec(continuePlaying, LIGHTGRAY);
                DrawText("CONTINUE",
                    WIDTH / 2 - MeasureText("CONTINUE", 20) / 2,
                    continuePlaying.y + 15, 20, BLACK);
            }
            else {
                DrawRectangleRec(continuePlaying, DARKGRAY);
                DrawText("CONTINUE",
                    WIDTH / 2 - MeasureText("CONTINUE", 20) / 2,
                    continuePlaying.y + 15, 20, WHITE);
            }

            if (CheckCollisionPointRec(GetMousePosition(), quitGame)) {
                DrawRectangleRec(quitGame, LIGHTGRAY);
                DrawText("QUIT GAME",
                    WIDTH / 2 - MeasureText("QUIT GAME", 20) / 2,
                    quitGame.y + 15, 20, BLACK);
            }
            else {
                DrawRectangleRec(quitGame, DARKGRAY);
                DrawText("QUIT GAME",
                    WIDTH / 2 - MeasureText("QUIT GAME", 20) / 2,
                    quitGame.y + 15, 20, WHITE);
            }

            break;
        }

        case GAME_OVER:
        {
            DrawRectangle(0, 0, WIDTH, HEIGHT, Fade(MAROON, 0.8f));

            DrawText("GAME OVER",
                WIDTH / 2 - MeasureText("GAME OVER", 50) / 2,
                200, 50, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), resetGame)) {
                DrawRectangleRec(resetGame, LIGHTGRAY);
                DrawText("RESTART", WIDTH / 2 - MeasureText("RESTART", 20) / 2,
                    resetGame.y + 15, 20, BLACK);
            }
            else {
                DrawRectangleRec(resetGame, DARKGRAY);
                DrawText("RESTART", WIDTH / 2 - MeasureText("RESTART", 20) / 2,
                    resetGame.y + 15, 20, WHITE);
            }

            break;
        }
        }

        EndDrawing();
    }

    //unloadEnemy(enemyTexture, MAX_TEXTURE);

    CloseWindow();
    return 0;
}
