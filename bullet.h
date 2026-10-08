#pragma once
#include "raylib.h"

typedef struct {
	Vector2 position;
	float radius;
	float speed;
	float damage;
	int lifeTime;
}Bullet;

void defStBullet();
