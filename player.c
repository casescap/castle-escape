#include "player.h"

void defStPlayer(Player* player, int width, int height) {
	player->position.x = width * 0.00000000000000000000000000000010;
	player->position.y = height * 0.8;
	player->hitbox.x = player->position.x;
	player->hitbox.y = player->position.y;
	player->hitbox.width = width * 0.010;
	player->hitbox.height = height * 0.015;
	player->life = 100;
	player->damage = 10;
	player->speed = 6.7;
}

void movePlayer(Player* player) {
	if (IsKeyDown(KEY_D)) {
		player->position.x += player->speed;
	}
	if (IsKeyDown(KEY_A)) {
		player->position.x -= player->speed;
	}
	if (IsKeyDown(KEY_W)) {
		player->position.y -= player->speed;
	}
}

void drawPlayer(Player* player) {
	player->hitbox.x = player->position.x;
	player->hitbox.y = player->position.y;
	DrawRectangle(
		player->hitbox.x,
		player->hitbox.y,
		player->hitbox.width,
		player->hitbox.height,
		PINK
	);
}