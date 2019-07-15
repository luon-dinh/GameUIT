#include "Global.h"

HINSTANCE hInstance = NULL;						
HWND hwnd = NULL;							
LPD3DXSPRITE spriteHandler = nullptr;		
LPDIRECT3DDEVICE9 d3ddev = nullptr;			

LPCSTR Global::WINDOW_CLASS_NAME = "Frame Work";
LPCSTR Global::GAME_TITLE = "Frame Work";
int Global::SCREEN_WIDTH = 256;
int Global::SCREEN_HEIGHT = 224;
int Global::MAX_FRAME_RATE = 90;
int Global::BALL_WIDTH = 40;
int Global::BALL_HEIGHT = 40;
int Global::BAT_WIDTH = 90;
int Global::BAT_HEIGHT = 30;
int Global::TIME_PER_FRAME = 150;
int Global::NORMALPLAYER_WIDTH = 40;
int Global::NORMALPLAYER_HEIGHT = 40;
int Global::TILE_SIZE = 16;
int Global::NUMBER_MAP = 1;

