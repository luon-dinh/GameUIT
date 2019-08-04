#include "Global.h"

HINSTANCE hInstance = NULL;
HWND hwnd = NULL;
LPD3DXSPRITE spriteHandler = nullptr;
LPDIRECT3DDEVICE9 d3ddev = nullptr;

char * AnimFilePath::WATER_TOP_ANIM = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\water_1.png";
char * AnimFilePath::WATER_BOTTOM_ANIM = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\water_2.png";
char * AnimFilePath::SEWER_ANIM = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\sewer.png";
char * AnimFilePath::EXIT_SIGN = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\exit.png";

//Định nghĩa ID của các object.
int ObjectID::GROUND = 0;
int ObjectID::SOLIDBOX = 1;
int ObjectID::WATERRL = 2;
int ObjectID::ROPE = 3;
int ObjectID::ONOFF = 4;
int ObjectID::WAVE = 5;
int ObjectID::DOOR = 6;
int ObjectID::SPIKE = 7;
int ObjectID::ITEMLOOTER = 8;
int ObjectID::BLUESOLDIER = 9;
int ObjectID::REDROCKET = 10;
int ObjectID::ITEMLOOTERMAP2 = 11;
int ObjectID::DISAPPEARING_PLATFORM = 12;
int ObjectID::MOVING_PLATFORM = 13;

//Định nghĩa trọng số render của các loại object khác nhau.
int RenderWeightOfObjects::BULLET_RENDER_WEIGHT = 3;
int RenderWeightOfObjects::ITEM_RENDER_WEIGHT = 1;
int RenderWeightOfObjects::OBJECT_RENDER_WEIGHT = 0;
int RenderWeightOfObjects::ENEMY_RENDER_WEIGHT = 2;