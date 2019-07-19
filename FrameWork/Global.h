#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

#define WINDOW_CLASS_NAME "Frame Work"		
#define GAME_TITLE "Frame Work"		
#define SCREEN_WIDTH 256						
#define SCREEN_HEIGHT 224			
#define MAX_FRAME_RATE 90						
#define BALL_WIDTH 40
#define BALL_HEIGHT 40
#define BAT_WIDTH 90
#define BAT_HEIGHT 30
#define TIME_PER_FRAME 120

//Normal Player Define
#define NORMALPLAYER_WIDTH			40
#define NORMALPALYER_HEIGHT			40
#define PLAYER_MAX_JUMPING_HEIGHT	500
#define PLAYER_NORMAL_SPEED			1.5
#define PLAYER_JUMP_SPEED			5
#define GROUND_GRAVITY				0.3
#define PLAYER_MAX_FALLING_VELOCITY -300
// Moving keyboard input
#define PLAYER_MOVE_LEFT			DIK_LEFTARROW
#define PLAYER_MOVE_RIGHT			DIK_RIGHTARROW
#define PLAYER_JUMP					DIK_SPACE
#define PLAYER_SIT					DIK_DOWNARROW 
#define PLAYER_ATTACK				DIK_Z
#define PLAYER_SHIELD_UP			DIK_UPARROW

#define DENTA_PIXEL 4

#define TILE_SIZE 16
#define NUMBER_MAP 190


class AnimFilePath
{
public:
	static char * WATER_TOP_ANIM;
	static char * WATER_BOTTOM_ANIM;
	static char * SEWER_ANIM;
	static char * EXIT_SIGN;
};

//Struct này dùng để lưu lại thông tin của player khi qua các màn khác nhau.
//Lưu ý đừng lưu máu vào đây, đây chỉ là để lưu vị trí và trạng thái của player.
//Máu của player sẽ được đi xuyên suốt khắp các màn mà không thay đổi.
struct PlayerInfo
{
	float playerX;
	float playerY;
};

enum Tag {

	PLAYER,
	ITEM,
	MAPCHARLES,
	MAPCHARLESBOSSLIGHT,
	MAPCHARLESBOSSDARK,
	TileSet1,
	MAPPITTSBURGHLIGHT,
	MAPPITTSBURGHDARK,
	MAPPITTSBURGHPORTAL1LIGHT,
	MAPPITTSBURGHPORTAL1DARK,
	MAPPITTSBURGHPORTAL2LIGHT,
	MAPPITTSBURGHPORTAL2DARK,
	MAPPITTSBURGHBOSS,
	TESTMAPOBJECTRED,
	TESTMAPOBJECTBLUE,
	ENERMY,
	BULLET,
	SHIELD,
	WATERTOP,
	WATERBOTTOM,
	SEWER,
	EXITSIGN
};
enum Type {
	NONE,
	CLOUD,
	BRICK,
	WIZARD,
	MINIBOSS,
	LOCOT,
	GROUND,
	SOLIDBOX,
	WATERRL,
	ROPE,
	ONOFF
	//cac loai dan
};

enum State {
	STANDING,
	RUNNING,
	WALKING,
	JUMPING,
	DASHING,
	FLYING,
	DUCKING,
	DEAD,
	ATTACKING,
	ATTACKING_STAND,
	DUCKING_PUNCHING,
	SWIMING,
	ATTACKING_FLY,
	FALLING,
	FLOATING,
	SHIELD_UP,
	ROLLING,
	KICKING
};

enum MapName
{
	CHARLES,
	CHARLESBOSSLIGHT,
	CHARLESBOSSDARK,
	PITTSBURGHLIGHT,
	PITTSBURGHDARK,
	PITTSBURGHPORTAL1LIGHT,
	PITTSBURGHPORTAL1DARK,
	PITTSBURGHPORTAL2LIGHT,
	PITTSBURGHPORTAL2DARK,
	PITTSBURGHBOSS,
	NOMAP
};

extern HINSTANCE hInstance;
extern HWND hwnd;
extern LPD3DXSPRITE spriteHandler;
extern LPDIRECT3DDEVICE9 d3ddev;