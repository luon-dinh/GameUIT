#include "MapPittsburghBoss.h"

MapPittsburghBoss::MapPittsburghBoss(const char * imgPath, const char * txtPath) : TileMap(imgPath, txtPath, Tag::MAPPITTSBURGHBOSS)
{
	caroUpAnim = new Animation(Tag::CARO_UP, 0, 4, delayCaroAnimation);
	caroDownAnim = new Animation(Tag::CARO_DOWN, 0, 4, delayCaroAnimation);
}

MapPittsburghBoss::~MapPittsburghBoss()
{
	if (caroUpAnim != nullptr)
		delete caroUpAnim;
	if (caroDownAnim != nullptr)
		delete caroDownAnim;
}

void MapPittsburghBoss::Draw(Camera* camera)
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
			if (tileID == CARO_UP_ANIM)
			{
				caroUpAnim->Render(viewPortPos);
			}
			else if (tileID == CARO_DOWN_ANIM)
			{
				caroDownAnim->Render(viewPortPos);
			}
			else
				tileSet->DrawTile(tileID, viewPortPos);
		}
	}
}

void MapPittsburghBoss::Update(double dt)
{
	caroUpAnim->Update(dt);
	caroDownAnim->Update(dt);
}