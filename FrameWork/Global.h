#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

//Define toán học.
#define PI 3.14159265
#define SQRT2 0.70710678118

#define WINDOW_CLASS_NAME "Captain America"		
#define GAME_TITLE "Captain America"		
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
#define PLAYER_JUMP_SPEED			5.5
#define PLAYER_MAX_FALLING_VELOCITY -300
#define PLAYER_DASH_SPEED			3

//shield define
#define SHIELD_SPEED 8;

#define GROUND_GRAVITY				0.17
#define WATER_SPEED					0.75

//item define
#define ITEM_SPEED 1
#define ITEM_EXIST_TIME 3000
//enemy define
#define ENEMY_BULLET_EXIST_TIME 3000
#define ENEMY_BULLET_SPEED 2
#define ENEMY_BEATEN_TIME 300
#define ENEMY_SPEED 1
//Red rockerter define
#define RED_ROCKERTER_STATE_TIME 2000

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

//Đây là một class dùng để lưu lại các quy định ID trong file xuất ra bởi Advanced Map Editor.
class ObjectID
{
public:
	static int GROUND;
	static int SOLIDBOX;
	static int WATERRL;
	static int ROPE;
	static int ONOFF;
	static int WAVE;
	static int DOOR;
	static int SPIKE;
	static int ITEMLOOTER;
	static int ITEMLOOTERMAP2;
	static int BLUESOLDIER;
	static int REDROCKET;
	static int DISAPPEARING_PLATFORM;
	static int MOVING_PLATFORM;
	static int GREENSOLDIER;
	static int WHITEFLYINGROBOT;
	static int WHITEROCKRTER;
	static int CANNON;
	static int EVIL_BAT;
	static int ELECTRIC_BAT;
};

//Đây là class chứa trọng số vẽ.
class RenderWeightOfObjects
{
public:
	static int OBJECT_RENDER_WEIGHT;
	static int ITEM_RENDER_WEIGHT;
	static int BULLET_RENDER_WEIGHT;
	static int ENEMY_RENDER_WEIGHT;
};

//Struct này dùng để lưu lại thông tin của player khi qua các màn khác nhau.
//Lưu ý đừng lưu máu vào đây, đây chỉ là để lưu vị trí và trạng thái của player.
//Máu của player sẽ được đi xuyên suốt khắp các màn mà không thay đổi.
struct PlayerInfo
{
	float playerX;
	float playerY;
};

struct CameraInfo
{
	float topLeftX;
	float topLeftY;
};
//dung cho enemy
enum RunType {
	THREESHOOTER = 0,
	NOTRUN = 1,
	CANRUN = 2,
	SPECIAL = 3,
};

enum RedRocketRobotType
{
	ONESIDED = 0,
	TWOSIDED = 1,
	TWOSIDEDNONLINEAR = 2,
	ONESIDEDJUMPING = 3
};

enum MovingPlatformType
{
	CIRCLE = 0,
	CROSSED = 1,
	HORIZONTAL = 2
};

enum ItemType {
	HALFHEART = 0,
	HEART = 1,
	SMALLGEM = 2,
	GEM = 3,
	HP = 4,
	UP = 5,
	EXIT = 6,
	STAR,
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
	PAUSESCENE,
	TESTMAPOBJECTRED,
	TESTMAPOBJECTBLUE,
	ENERMY,
	ENEMYEXPLODE,
	SHIELD,
	WATERTOP,
	WATERBOTTOM,
	SEWER,
	EXITSIGN,
	ITEMCONTAINER,
	ITEMCONTAINERMAP2,
	BLUESOLDIER,
	STATICOBJECT,
	BLUESOLDERBULLET,
	BULLET,
	BULLETEXPLODE,
	REDROCKERTERBULLET,
	WHITEROCKERTERBULLET,
	GREENCANNONBULLET,
	WHITEFLYROBOTBULLET,
	GREENSOLDIER,
	//Theo chiều kim đồng hồ. Bắt đầu từ vị trí hướng lên trên.
	WHITEFLYINGROBOTBULLET,
	WHITEFLYINGROBOT,
	REDROCKERTER,
	WHITEROCKERTER,
	BOSSWIZARD,
	BOSSWIZARDBULLET,
	BOSSMINI,
	BOSSMINIBULLET,
	HP_RENDER,
	PLAYER_PART,
	EVIL_BAT,
	MOVING_PLATFORM_VERTICAL_FIRE,
	MOVING_PLATFORM_HORIZONTAL_FIRE,
	MOVING_PLATFORM,
	DISAPPEARING_PLATFORM,
	SPLIT_BRICK,
	DOOR_DARK,
	DOOR_LIGHT,
	ELECTRIC_SHOCKWAVE,
	CANON,
	CARO_UP,
	CARO_DOWN,
	PLAYER_HANG
};

enum Type {
	NONE = 0,
	CLOUD = 1,
	BRICK = 2,
	WIZARD = 3,
	MINIBOSS = 4,
	LOCOT = 5,
	GROUND = 6,
	SOLIDBOX = 7,
	WATERRL = 8,
	ROPE = 9,
	ONOFF = 10,
	DOOR = 11,
	ITEMCONTAINERTYPE = 12,
	ENEMY = 13,
	BULLETTYPE = 14,
	PLATFORM = 15,
	SHOCKWAVE = 16,
	SPIKE = 17
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
	DUCKING_PUNCHING,
	ATTACKING_FLY,
	FALLING,
	FLOATING,
	SHIELD_UP,
	SHIELD_DOWN,
	ROLLING,
	KICKING,
	DIVING,
	SHIELD_ATTACK,
	STAND_PUNCH,
	BEATEN,
	FLYING_BEATEN,
	CLIMBING,
	STAND_SMILE,
	ATTACK,
	SHOCKING
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
	PAUSESCENEMAPNAME,
	NOMAP
};

extern HINSTANCE hInstance;
extern HWND hwnd;
extern LPD3DXSPRITE spriteHandler;
extern LPDIRECT3DDEVICE9 d3ddev;