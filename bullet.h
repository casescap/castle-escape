#pragma once
#include "raylib.h"


#define MAX_BULLETS 100
typedef struct Enemy Enemy;
typedef struct Player Player;

typedef enum {
	BULLET_PLAYER,
	BULLET_SKELETON,
	BULLET_SLIME
}bulletType;

typedef struct Bullet {
	Vector2 position;
	Vector2 direction;
	float radius;
	float speed;
	float damage;
	int lifeTime;
	bool active;
	bulletType type;
	float bulletCd;
}Bullet;

void defStBullet(Bullet *bullet, Vector2 initialPosition, Vector2 direction, bulletType type, Player *player);
void spawnBullet(Bullet bullets[],int mAX_BULLETS, Vector2 initialPosition, Vector2 direction, bulletType type, Player *player);
void drawBullet(Bullet bullet[], int mAX_BULLETS);
void updateBullet(Bullet bullet[], int mAX_BULLETS);
void checkBulletColl(Bullet bullet[], int MAX_BULLET, Enemy enemy[], int MAX_ENEMY, Player *player);