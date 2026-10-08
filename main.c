#include "raylib.h"
#include "resource_dir.h"	
#include "player.h"
#include "enemy.h"

#define WIDTH 1280
#define HEIGHT 720
#define MAX_ENEMY 800

Player player;
Texture2D enemyTexture[10];
Enemy enemy[MAX_ENEMY];
int enemySpawnCd = 10;
int enemySpawnCdMax = 10;

int main ()
{
	
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	SetTargetFPS(60);
	
	InitWindow(WIDTH, HEIGHT, "Hello Raylib");

	SearchAndSetResourceDir("resources");

	defStPlayer(&player, WIDTH, HEIGHT);
	loadEnemy(enemyTexture);
	while (!WindowShouldClose())		
	{
		movePlayer(&player);
		moveEnemy(enemy, MAX_ENEMY, &player);

		if (enemySpawnCd >= enemySpawnCdMax) {
			spawnEnemy(enemy, ENEMY_SLIME, MAX_ENEMY, &player, WIDTH, HEIGHT);
		}
		else enemySpawnCd++;

		BeginDrawing();

		ClearBackground(BLACK);

		drawPlayer(&player);
		drawEnemy(enemy, MAX_ENEMY, enemyTexture);
		
		EndDrawing();
	}

	

	CloseWindow();
	return 0;
}
