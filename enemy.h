#pragma once
#include "raylib.h"
#include "player.h"

typedef enum {
	ENEMY_SLIME
} EnemiesType;

typedef struct {
	float life;
	float damage;
	float speed;
	Rectangle hitbox;
	Vector2 position;
	EnemiesType type;
	bool active;
}Enemy;

void defEnemySt(Enemy* enemy, int x, int y, int width, int height, EnemiesType type);
void spawnEnemy(Enemy enemy[], EnemiesType type, int MAX_ENEMY, Player* player, int width, int height);
void drawEnemy(Enemy enemy[], int MAX_ENEMY, Texture2D enemyTexture[]);
void loadEnemy(Texture2D enemyTexture[]);
void moveEnemy(Enemy enemy[], int MAX_ENEMY, Player* player);