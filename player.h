#pragma once

#include "raylib.h"


typedef struct {
	Rectangle hitbox;
	Vector2 position;
	float life;
	float damage;
	float speed;
} Player;

void defStPlayer(Player* player, int width, int height);
void movePlayer(Player* player);
void drawPlayer(Player* player);
