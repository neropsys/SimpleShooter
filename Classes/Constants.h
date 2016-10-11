#pragma once
#define PLAYER "Player"
#define ENEMY "Enemy"
//player contact event mask
#define PLAYER_MASK 168
#define PLAYER_PROJ_MASK 80
//enemy contact event mask
#define ENEMY_MASK 48
#define ENEMY_PROJ_MASK 8

//meteorite contact event mask
#define METEORITE_MASK 192

//projectile space for preventing collision
#define PROJ_SPACE 0
//game object space for preventing collision
#define OBJ_SPACE 0
/*
Player    10101000
Playerprj 01010000
Meteorite 11000000
Enemy     00110000
Enemyprj  00001000
projSpace 00000000
objSpace  00000000
*/