#pragma once

#include "raylib.h"


typedef struct Player {
	Rectangle hitbox;
	Vector2 position;
	float life;
	float damage;
	float speed;
	bool tanochao;
	float vspeed;
	float damageCd;
	float damageCdMax;
} Player;

void defStPlayer(Player *player, int width, int height);
void movePlayer(Player *player, Rectangle chao[]);
void drawPlayer(Player *player);
void killPlayer(Player *player);
void updatePlayer(Player *player, Rectangle chao[]);
/*void unloadPlayer(); player n tem textura ainda*/
