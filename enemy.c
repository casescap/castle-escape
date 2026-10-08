#include "raylib.h"
#include "enemy.h"


void defEnemySt(Enemy* enemy, int x, int y, int width, int height, EnemiesType type){
	switch (type) {
	case ENEMY_SLIME:
		enemy->position.x = x;
		enemy->position.y = y;
		enemy->hitbox.x = enemy->position.x;
		enemy->hitbox.y = enemy->position.y;
		enemy->hitbox.width = width * 0.9;
		enemy->hitbox.height = height * 0.99;
		enemy->active = true;
		break;
	}
}

void spawnEnemy(Enemy enemy[], EnemiesType type, int MAX_ENEMY, Player* player, int width, int height) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].active) continue; 
		//refazer mais tarde o algoritmo de spawn de inimigos
		float x, y;
		x = player->position.x + width*0.12;
		y = player->position.y + height*0.15;

		switch (type) {
		case ENEMY_SLIME:
			defEnemySt(&enemy[i], x, y, width, height, type);
			break;
		}
	}
}

void drawEnemy(Enemy enemy[], int MAX_ENEMY, Texture2D enemyTexture[]) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].active) continue;
		switch (enemy[i].type) {
		case ENEMY_SLIME:
			DrawTexture(
				enemyTexture[ENEMY_SLIME],
				enemy->position.x,
				enemy->position.y,
				WHITE
			);
			break;
		}
	}
}

void loadEnemy(Texture2D enemyTexture[]) {
	enemyTexture[ENEMY_SLIME] = LoadTexture("bolsonaro.png");
}

void moveEnemy(Enemy enemy[], int MAX_ENEMY, Player* player) {
	float dist;
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].active) continue;
		dist = player->position.x - enemy->position.x;
		if (dist > 0) {
			enemy->position.x += enemy->speed;
		}
		else {
			enemy->position.x -= enemy->speed;
		}
	}
}