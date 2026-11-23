#include "player.h"

void defStPlayer(Player *player, int width, int height) {
	player->position.x = width * 0.10;
	player->position.y = height * 0.8;
	player->hitbox.x = player->position.x;
	player->hitbox.y = player->position.y;
	player->hitbox.width = width * 0.010;
	player->hitbox.height = height * 0.015;
	player->life = 100;
	player->damage = 100;
	player->speed = 6.7;

	player->damageCd = 0;
	player->damageCdMax = 1.5f;
}

void movePlayer(Player *player, Rectangle chao[]) {
	if (IsKeyDown(KEY_D)) {
		player->position.x += player->speed;
	}
	if (IsKeyDown(KEY_A)) {
		player->position.x -= player->speed;
	}
	if (IsKeyDown(KEY_W) && player->tanochao) {
		player->vspeed = -10; 
		player->tanochao = false;
	}
	if (!player->tanochao) {
		player->vspeed += 0.5f; 
		player->position.y += player->vspeed;

		player->hitbox.x = player->position.x;
		player->hitbox.y = player->position.y;
	}
	if (CheckCollisionRecs(player->hitbox, chao[0])) {
		if (player->vspeed >= 0) {
			player->position.y = chao[0].y - player->hitbox.height;
			player->hitbox.y = player->position.y;

			player->vspeed = 0;
			player->tanochao = true;
		}
	}
	else {
		player->tanochao = false;
	}

}

void drawPlayer(Player *player) {
	player->hitbox.x = player->position.x;
	player->hitbox.y = player->position.y;
	DrawRectangle(player->hitbox.x, player->hitbox.y, player->hitbox.width, player->hitbox.height, PINK);
}

void killPlayer(Player *player) { 
	if (player->life <= 0) {
		player->vspeed = 0;
		player->speed = 0;
	}
}

void updatePlayer(Player *player, Rectangle chao[]) {
	movePlayer(&player, chao);

	if (player->life <= 0) {
	killPlayer(&player);
	}
}
