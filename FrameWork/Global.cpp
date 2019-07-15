#include "Global.h"

HINSTANCE hInstance = NULL;
HWND hwnd = NULL;
LPD3DXSPRITE spriteHandler = nullptr;
LPDIRECT3DDEVICE9 d3ddev = nullptr;

char * AnimFilePath::WATER_TOP_ANIM = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\water_1.png";
char * AnimFilePath::WATER_BOTTOM_ANIM = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\water_2.png";
char * AnimFilePath::SEWER_ANIM = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\Animation\\sewer.png";