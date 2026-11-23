#include "raylib.h"
#include "enemy.h"
#include "raymath.h"
#include "bullet.h"

void inicializar(SpawnQueue *q){
	q->inicio = 0;
	q->fim = 0;
	q->quantidade = 0;
}

bool enqueue(SpawnQueue *q, EnemiesType type, float delay) {
	if (q->quantidade >= MAX_QUEUE) return false;

	q->spawn[q->fim].type = type;
	q->spawn[q->fim].delay = delay;
	q->fim = (q->fim + 1) % MAX_QUEUE;
	q->quantidade++;
	return true;
}

bool dequeue(SpawnQueue *q, EnemiesType *type, float time){
	if (q->quantidade <= 0) return false;

	q->spawn[q->inicio].delay -= time;

	if (q->spawn[q->inicio].delay > 0) return false;

	*type = q->spawn[q->inicio].type;
	q->inicio = (q->inicio + 1) % MAX_QUEUE;
	q->quantidade--;
	return true;

}

void defEnemySt(Enemy *enemy, int x, int y, int width, int height, EnemiesType type){
	switch (type) {
	case ENEMY_SLIME:
		enemy->position.x = x;
		enemy->position.y = y;
		enemy->hitbox.x = x;
		enemy->hitbox.y = y;
		enemy->hitbox.width = width * 0.035;
		enemy->hitbox.height = height * 0.035;
		enemy->speed = 2;
		enemy->type = type;
		enemy->life = 10;
		enemy->active = true;
		enemy->enemyShootCd = 4.0f;
		break;

	case ENEMY_SKELETON:
		enemy->position.x = x;
		enemy->position.y = y;
		enemy->hitbox.x = enemy->position.x;
		enemy->hitbox.y = enemy->position.y;
		enemy->hitbox.width = width * 0.035;
		enemy->hitbox.height = height * 0.035;
		enemy->speed = 2;
		enemy->type = type;
		enemy->life = 40;
		enemy->active = true;
		enemy->enemyShootCd = 2.0f;
		break;
		
	case ENEMY_GHOST:
		enemy->position.x = x;
		enemy->position.y = y;
		enemy->hitbox.x = enemy->position.x;
		enemy->hitbox.y = enemy->position.y;
		enemy->hitbox.width = width * 0.035;
		enemy->hitbox.height = height * 0.035;
		enemy->speed = 2;
		enemy->life = 40;
		enemy->type = type;
		enemy->active = true;
		break;

	}
}

void spawnEnemy(Enemy enemy[], EnemiesType type, int MAX_ENEMY, Player *player, int width, int height) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].active) continue;

		float x, y;

		switch (type) {
		case ENEMY_SLIME:
			x = player->position.x + width * 0.12;
			y = player->position.y + height * 0.15;
			defEnemySt(&enemy[i], x, y, width, height, type);
			break;

		case ENEMY_SKELETON:
			x = player->position.x + width * 0.30;
			y = player->position.y + height * 0.15;
			defEnemySt(&enemy[i], x, y, width, height, type);
			break;

		case ENEMY_GHOST:
			x = player->position.x + width * 0.45;
			y = player->position.y + height * 0.15;
			defEnemySt(&enemy[i], x, y, width, height, type);
			break;
		}

		break; 
	}
}

void drawEnemy(Enemy enemy[], int MAX_ENEMY) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].active) continue;
		switch (enemy[i].type) {
		case ENEMY_SLIME:
			//DrawTextureEx(enemyTexture[ENEMY_SLIME], enemy[i].position, 0, 0.05f, WHITE);
			DrawRectangle(enemy[i].hitbox.x, enemy[i].hitbox.y, enemy[i].hitbox.width, enemy[i].hitbox.height, ORANGE);
		case ENEMY_SKELETON:
			DrawRectangle(enemy[i].hitbox.x, enemy[i].hitbox.y, enemy[i].hitbox.width, enemy[i].hitbox.height, RED);
			break;
		case ENEMY_GHOST:
			DrawRectangle(enemy[i].hitbox.x, enemy[i].hitbox.y, enemy[i].hitbox.width, enemy[i].hitbox.height, GREEN);
		}
	}
}

/*void loadEnemy(Texture2D enemyTexture[]) {

	enemyTexture[ENEMY_SLIME] = LoadTexture();

	enemyTexture[ENEMY_SKELETON] = LoadTexture();

	enemyTexture[ENEMY_GHOST] = LoadTexture();
}*/

void moveEnemy(Enemy enemy[], int MAX_ENEMY, Player* player) {
	Vector2 dist;
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].active) continue;
		dist = Vector2Subtract(player->position, enemy[i].position);
		dist = Vector2Normalize(dist);

		enemy[i].position.x += enemy[i].speed * dist.x;
		enemy[i].position.y += enemy[i].speed * dist.y;

		enemy[i].hitbox.x = enemy[i].position.x;
		enemy[i].hitbox.y = enemy[i].position.y;

	}
}

void checkColl(Enemy enemy[], int MAX_ENEMY, Player *player) {
	bool active = false;
	if (player->damageCd > 0) {
		player->damageCd -= 1;
	}
	else {
		player->damage = 0;
		active = true;
	}
	if (!active) return;


	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].active) continue;

		if (CheckCollisionRecs(enemy[i].hitbox, player->hitbox)) {

			player->life -= enemy[i].damage;
			player->damageCd = player->damageCdMax;
		}
	}
}


void updateEnemy(Enemy enemy[], int MAX_ENEMY, Player *player, Bullet bullets[]) {
	moveEnemy(enemy, MAX_ENEMY, player);

	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].active) continue;

		if (enemy[i].life <= 0) {
			enemy[i].active = false;
			continue;
		}

		if (enemy[i].type == ENEMY_GHOST) continue;

		enemy[i].enemyShootCd -= GetFrameTime(); //usar uma constante aqui realmenta da um problema cabeludo

		if (enemy[i].enemyShootCd <= 0) {
			Vector2 enemyCenter = {
				enemy[i].position.x + (enemy[i].hitbox.width / 2.0f),
				enemy[i].position.y + (enemy[i].hitbox.height / 2.0f)
			};

			Vector2 playerCenter = {
				player->hitbox.x + player->hitbox.width / 2.0f,
				player->hitbox.y + player->hitbox.height / 2.0f
			};

			Vector2 direction = Vector2Subtract(playerCenter, enemyCenter);
			direction = Vector2Normalize(direction);

			if (direction.x == 0 && direction.y == 0) {
				direction.x = 1.0f;
				direction.y = 0.0f;
			}

			bulletType defType;

			if (enemy[i].type == ENEMY_SKELETON) {
				defType = BULLET_SKELETON;
			}
			else {
				defType = BULLET_SLIME;
			}

			spawnBullet(bullets, MAX_BULLETS, enemyCenter, direction, defType, player);

			switch (enemy[i].type) {
			case ENEMY_SKELETON:
				enemy[i].enemyShootCd = 2.0f;
				break;

			case ENEMY_SLIME:
				enemy[i].enemyShootCd = 4.0f;
				break;
			}
		}
	}
}


/*void unloadEnemy(Texture2D enemyTexture[], int MAX_TEXTURE) {
	for (int i = 0; i < MAX_TEXTURE; i++) {
		UnloadTexture(enemyTexture[i]);
	}
}*/
