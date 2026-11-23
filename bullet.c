#include "raylib.h"
#include "raymath.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"

void defStBullet(Bullet* bullet, Vector2 initialPosition, Vector2 direction, bulletType type, Player *player) {
	switch (type) {
	case BULLET_PLAYER:
		bullet->position = initialPosition;
		bullet->direction = direction;
		bullet->radius = 4;
		bullet->speed = 6;
		bullet->damage = player->damage;
		bullet->lifeTime = 300;
		bullet->type = type;
		bullet->bulletCd = 1.0f;
		break;
	case BULLET_SKELETON:
		bullet->position = initialPosition;
		bullet->direction = direction;
		bullet->radius = 4;
		bullet->speed = 6;
		bullet->damage = 15;
		bullet->lifeTime = 300;
		bullet->type = type;
		bullet->bulletCd = 2.0f;
		break;
	case BULLET_SLIME:
		bullet->position = initialPosition;
		bullet->direction = direction;
		bullet->radius = 4;
		bullet->speed = 2;
		bullet->damage = 10;
		bullet->lifeTime = 300;
		bullet->type = type;
		bullet->bulletCd = 4.0f;
		break;

	}
}	

void spawnBullet(Bullet bullets[], int mAX_BULLETS, Vector2 initialPosition, Vector2 direction, bulletType type, Player *player) {
	for (int i = 0; i < mAX_BULLETS; i++) {
		if (bullets[i].active) continue;


		defStBullet(&bullets[i], initialPosition, direction, type, player);
		bullets[i].active = true;
		break;

	}
}

void drawBullet(Bullet bullet[], int mAX_BULLETS) {
	for (int i = 0; i < mAX_BULLETS; i++) {
		if (!bullet[i].active) continue;


		if (bullet[i].type == BULLET_PLAYER) {
			DrawCircleV(bullet[i].position, bullet[i].radius, BLUE);
		}
		if (bullet[i].type == BULLET_SKELETON) {
			DrawCircleV(bullet[i].position, bullet[i].radius, ORANGE);
		}
		if (bullet[i].type == BULLET_SLIME) {
			DrawCircleV(bullet[i].position, bullet[i].radius, RED);
		}
	}  
}

void updateBullet(Bullet bullet[], int mAX_BULLETS) {
	for (int i = 0; i < mAX_BULLETS; i++) {
		if (!bullet[i].active) continue;

		bullet[i].position.x += bullet[i].direction.x * bullet[i].speed; 
		bullet[i].position.y += bullet[i].direction.y * bullet[i].speed;

		bullet[i].lifeTime -= 1;

		if (bullet[i].lifeTime <= 0) {
			bullet[i].active = false;
		}

	}
}

void checkBulletColl(Bullet bullet[], int mAX_BULLET, Enemy enemy[], int MAX_ENEMY, Player *player) {
	for (int i = 0; i < mAX_BULLET; i++) {
		if (!bullet[i].active) continue;

		if (bullet[i].type == BULLET_PLAYER) {
			for (int j = 0; j < MAX_ENEMY; j++) {
				if (!enemy[j].active) continue;

				if (CheckCollisionCircleRec(bullet[i].position, bullet[i].radius, enemy[j].hitbox)) {
					bullet[i].active = false;
					enemy[j].life -= bullet[i].damage;
					break;
				}
			}
		}
		else {
			if (CheckCollisionCircleRec(bullet[i].position, bullet[i].radius, player->hitbox)) {
				bullet[i].active = false;
				player->life -= bullet[i].damage;
			}
		}
	}
}
