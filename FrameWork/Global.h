#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
#define WINDOW_CLASS_NAME "Frame Work"		
#define GAME_TITLE "Frame Work"		
#define SCREEN_WIDTH 360						
#define SCREEN_HEIGHT 300			
#define MAX_FRAME_RATE 90						
#define BALL_WIDTH 40
#define BALL_HEIGHT 40
#define BAT_WIDTH 90
#define BAT_HEIGHT 30
#define TIME_PER_FRAME 150

			//Normal Player Define
#define NORMALPLAYER_WIDTH 40
#define NORMALPALYER_HEIGHT 40
#define SCREEN_TRANSLATEY 60

#define TILE_SIZE 16
#define NUMBER_MAP 1


enum Tag {

	PLAYER,
	ITEM,
	GROUND,
	MAP1,
	MAP2,
	MAP3,
	MAP4,
	ENERMY,
	BULLET,
	SHIELD
};

enum Type {
	NONE,
	CLOUD,
	BRICK,
	WIZARD,
	MINIBOSS,
	LOCOT,
	//cac loai dan
};

enum State {
	STANDING,
	RUNNING,
	WALKING,
	JUMPING,
	DASHING,
	FLYING,
	SITTING,
	DEAD,
	ATTACKING,
	ATTACKING_STAND,
	ATTACKING_SIT,
	SWIMING,
	ATTACKING_FLY,
	FALLING
};



extern HINSTANCE hInstance;									
extern HWND hwnd;												
extern LPD3DXSPRITE spriteHandler;								
extern LPDIRECT3DDEVICE9 d3ddev;								