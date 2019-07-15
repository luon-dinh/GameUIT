#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

class Global{
public:
	static LPCSTR WINDOW_CLASS_NAME;
	static LPCSTR GAME_TITLE;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static int MAX_FRAME_RATE;
	static int BALL_WIDTH;
	static int BALL_HEIGHT;
	static int BAT_WIDTH;
	static int BAT_HEIGHT;
	static int TIME_PER_FRAME;
	static int NORMALPLAYER_WIDTH;
	static int NORMALPLAYER_HEIGHT;
	static int SCREEN_TRANSLATEY;
	static int TILE_SIZE;
	static int NUMBER_MAP;

	enum Tag {

		PLAYER,
		ITEM,
		GROUND,
		MAP1,
		TileSet1,
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
		GROUND,
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
};





extern HINSTANCE hInstance;									
extern HWND hwnd;												
extern LPD3DXSPRITE spriteHandler;								
extern LPDIRECT3DDEVICE9 d3ddev;								