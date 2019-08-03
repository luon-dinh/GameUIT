#include "DrawDebug.h"

void DrawDebug::DrawBoundingBox(BoundingBox objectBox, Tag colorTag)
{
	D3DSURFACE_DESC texture_info;
	TextureManager::getInstance()->getTexture(colorTag)->GetLevelDesc(0, &texture_info);

	int tileSize = texture_info.Height;
	Sprite * debugSprite = new Sprite(colorTag, 0, 0, tileSize, tileSize);

	int objTopLeftX = objectBox.left;
	int objTopLeftY = objectBox.top;
	int objMostRight = objectBox.right;
	int objMostBottom = objectBox.bottom;
	float midX = (float)(objTopLeftX + objMostRight) / 2;
	float midY = (float)(objTopLeftY + objMostBottom) / 2;
	int curX = objTopLeftX;
	int curY = objTopLeftY;
	//Vẽ từ dưới lên, từ trái qua phải.
	while (curY - tileSize >= objMostBottom)
	{
		while (curX + tileSize < objMostRight)
		{
			D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(curX + tileSize / 2, curY - tileSize / 2, 0));
			debugSprite->Render(viewPort);
			curX += tileSize; 
		}
		curY -= tileSize;
		curX = objTopLeftX;
		//curY -= 1;
	}
	//Tô viền phải và viền dưới.
	curY = objMostBottom + tileSize;
	curX = objTopLeftX;
	while (curX + tileSize < objMostRight)
	{
		D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(curX + tileSize / 2, curY - tileSize / 2, 0));
		debugSprite->Render(viewPort);
		curX += tileSize;
	}
	curX = objMostRight - tileSize;
	curY = objTopLeftY;
	while (curY - tileSize >= objMostBottom)
	{
		D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(curX + tileSize / 2, curY - tileSize / 2, 0));
		debugSprite->Render(viewPort);
		curY -= tileSize;
	}
	//Tô nốt cục phải cùng dưới.
	curX = objMostRight - tileSize;
	curY = objMostBottom + tileSize;
	D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(curX + tileSize / 2, curY - tileSize / 2, 0));
	debugSprite->Render(viewPort);
	delete debugSprite;
	//D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(midX, midY, 0));
	//debugSprite->Render(objMostRight - objTopLeftX, objTopLeftY - objMostBottom, D3DXVECTOR2(viewPort.x, viewPort.y));
}