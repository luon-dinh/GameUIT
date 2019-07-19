#include "MapCharles.h"

MapCharles::MapCharles(const char * imgPath, const char * txtPath) : TileMap(imgPath, txtPath, Tag::MAPCHARLES)
{
	waterTopAnim = new Animation(Tag::WATERTOP, 0, 3, delayWaterFlow);
	waterBottomAnim = new Animation(Tag::WATERBOTTOM, 0, 3, delayWaterFlow);
	sewerAnim = new Animation(Tag::SEWER, 0, 3, delaySewerFlow);
	exitSign = new Animation(Tag::EXITSIGN, 0, 2, delayExitSignFlash);
}

MapCharles::~MapCharles()
{
	if (waterTopAnim != nullptr)
		delete waterTopAnim;
	if (waterBottomAnim != nullptr)
		delete waterBottomAnim;
	if (sewerAnim != nullptr)
		delete sewerAnim;
	if (exitSign != nullptr)
		delete exitSign;
}

void MapCharles::Update(double dt)
{
	waterTopAnim->Update(dt);
	waterBottomAnim->Update(dt);
	sewerAnim->Update(dt);
	exitSign->Update(dt);
}

void MapCharles::Draw(Camera* camera)
{
	//StartRow, EndRow, StartCol, EndCol lúc nào cũng phải bao srcRECT 1 tile.
//Quét theo chiều từ dưới lên, từ trái qua phải.

	RECT srcRECT = camera->getCameraRECT();

	int startCol = srcRECT.left / (tileSize)-1;
	int endCol = srcRECT.right / (tileSize)+1;
	int startRow = srcRECT.bottom / (tileSize)-1;
	int endRow = srcRECT.top / (tileSize)+1;

	int curRow = 0;
	int curCol = 0;
	for (int i = startRow; i <= endRow; ++i)
	{
		//Vẽ từng hàng ngang.
		//Xét điều kiện : Nếu hàng đang tính vẽ mà nằm ngoài map thì phải chỉnh lại.
		if (i < 0 || i >= maxRow)
			continue;
		curRow = i;
		for (int j = startCol; j <= endCol; ++j)
		{
			if (j < 0 || j >= maxCol)
				continue;

			curCol = j;

			int tileID = tileMap[curRow][curCol]; //Lấy tileID từ file text.

			//Tính toạ độ thực tế, xem ở WorldPort thì tile này sẽ vẽ ở đâu.
			D3DXVECTOR3 worldPos(curCol * tileSize + tileSize / 2, curRow * (tileSize)+tileSize / 2, 0);
			D3DXVECTOR3 viewPortPos = camera->convertWorldToViewPort(worldPos);
			if (tileID == SEWER_ANIM_ID)
			{
				sewerAnim->Render(viewPortPos);
			}
			else if (tileID == WATER_TOP_ANIM_ID)
			{
				waterTopAnim->Render(viewPortPos);
			}
			else if (tileID == WATER_BOTTOM_ANIM_ID)
			{
				waterBottomAnim->Render(viewPortPos);
			}
			else if (tileID == EXIT_SIGN_BEGIN_ID)
			{
				//ExitSign bự hơn so với cái tile khác.
				//Vì vậy ta phải chỉnh lại toạ độ vẽ của ExitSign.
				worldPos.x = worldPos.x + tileSize / 2;
				viewPortPos = camera->convertWorldToViewPort(worldPos);
				exitSign->Render(viewPortPos);
			}
			else if (tileID == EXIT_SIGN_END_ID)
			{
				//Không làm gì hết do exitSign chiếm tận 32 pixel theo hàng ngang.
			}
			else
				tileSet->DrawTile(tileID, viewPortPos);
		}
	}
}