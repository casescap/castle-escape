#pragma once
#include "raylib.h"
#include "player.h"

typedef struct Bullet Bullet;
typedef struct Player Player;

#define MAX_QUEUE 100

typedef enum {
	ENEMY_SLIME,
	ENEMY_SKELETON,
	ENEMY_GHOST 
} EnemiesType;

typedef struct Enemy {
	float life;
	float speed;
	float damage;
	Rectangle hitbox;
	Vector2 position;
	EnemiesType type;
	bool active;
	float enemyShootCd;
	bool tanochao;
	float vspeed;
}Enemy;

typedef struct {
	EnemiesType type;
	float delay;
} SpawnReq;

typedef struct {
	SpawnReq spawn[MAX_QUEUE];
	int inicio;
	int fim;
	int quantidade;
}SpawnQueue;

void inicializar(SpawnQueue *q);
bool enqueue(SpawnQueue *q, EnemiesType type, float delay);
bool dequeue(SpawnQueue *q, EnemiesType *type, float time);


void defEnemySt(Enemy *enemy, int x, int y, int width, int height, EnemiesType type);
void spawnEnemy(Enemy enemy[], EnemiesType type, int MAX_ENEMY, Player* player, int width, int height);
void drawEnemy(Enemy enemy[], int MAX_ENEMY);
//void loadEnemy(Texture2D enemyTexture[]);
void moveEnemy(Enemy enemy[], int MAX_ENEMY, Player* player); 
void checkColl(Enemy enemy[], int MAX_ENEMY, Player* player);
void updateEnemy(Enemy enemy[], int MAX_ENEMY, Player* player, Bullet bullets[]);
//void unloadEnemy(Texture2D enemyTexture[], int MAX_TEXTURE);