#pragma once

enum ObjectCamp {
	ALLYCAMP = 1<<1,
	ENEMYCAMP = 1<<2
};

enum Block {
	NO_BLOCK = 1 << 1, 
	LEFT_BLOCK = 1 << 2,
	RIGHT_BLOCK = 1 << 3,
};
enum PlayerClass {
	ROCKMAN_COMMON,
	ROCKMAN_ARMOR_ULTIMATE,
	ZERO_COMMON
};

enum PlayerState {
	// 공용
	STATE_COMIDLE = 1 << 1,
	STATE_COMJUMP = 1 << 2,
	STATE_COMRUN  = 1 << 3,
	STATE_SHOTIDLE= 1 << 4,
	STATE_SHOTRUN = 1 << 5,
	STATE_SHOTJUMP = 1 << 6,
	STATE_DASHSTART = 1 << 7,
	STATE_DASHING = 1 << 8,
	STATE_DASHSTOP = 1 << 9,
	STATE_SHOTDASH = 1 << 10,
	STATE_ATTACHTOWALL = 1 << 11,
	STATE_ATTACHTOWALL_KICKUP = 1 << 12,
	// X 전용
	STATE_FALLDOWN = 1 << 13,
	STATE_GAMESTART = 1 << 14,
	// Blade-Armor X 전용
	STATE_FLY_HORIZON = 1 << 15,
	STATE_FLY_VERTICAL_UP = 1 << 16,
	STATE_FLY_VERTICAL_DOWN = 1 << 17,
	STATE_BLADE_NORMAL = 1 << 18,
	STATE_BLADE_JUMP = 1 << 19,
	STATE_BLADE_ATTACHTOWALL = 1 << 20,

	STATE_XBUSTER = 1 << 21,
	STATE_XBUSTERCHARGE1 = 1 << 22,
	STATE_XBUSTERCHARGE2 = 1 << 23
};
enum EnemyAnimState {
};

enum StateIdentify {
	BASE_ID,
	STARTSTATE_ID,
	IDLESTATE_ID,
	JUMPSTATE_ID,
	MOVESTATE_ID,
	SHOTSTATE_ID,
	DASHSTATE_ID,
	LANDWALLSTATE_ID,
	GAMEOVERSTATE_ID,

	// enemy
	E_DAMAGE_ID,
	E_DETECTION_ID,
	E_ATTACK_ID
}; 
 
enum InstanceType {
	PROJECTILE = 1 << 1, 
	NEARATK = 1 << 2,
};

enum InstanceObjType {
	ROCKMAN_BUSTER_NC = 1 << 1,
	ROCKMAN_BUSTER_CR1 = 1 << 2,
	ROCKMAN_BUSTER_CR2 = 1 << 3,
	ROCKMAN_SABER = 1 << 4,
	ZERO_SABER_CB1,
	ZERO_SABER_CB2,
	ZERO_SABER_CB3,
};

typedef enum InstanceObjTypeForEnemy {
	DOMBA_BULLET,
	GUADERMAN_BULLET,
}E_ATK_OBJ;

enum ColliderType {
	RECT_COLLIDER = 1 << 1,
	CIRCLE_COLLIDER = 1 << 2,
	PIXEL_COLLIDER = 1 << 3
};

enum EnemyType {
	E_TYPE_DOMBA,
	E_TYPE_CROLLER,
	E_TYPE_1BOSS,
};

