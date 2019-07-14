#include "GameMap.h"
#include <fstream>
#include <sstream>

GameMap::GameMap(const char * _imgPath,  const char * _txtPath, const char * _mapObjectPath)
{
	this->imgPath = _imgPath;
	this->txtPath = _txtPath;
	this->mapObjectPath = _mapObjectPath;
	tMap = new TileMap(imgPath, txtPath);
	camera = Camera::getCameraInstance();
	D3DXIMAGE_INFO mapInfo;

	TextureManager::getInstance()->addTexture(Tag::MAP1, _imgPath);
	
	mapHeight = mapInfo.Height;
	mapWidth = mapInfo.Width;

	//Load tất cả những đối tượng liên quan đến map như Ground, Animation,..
	//LoadContent();
}

void GameMap::LoadContent()
{
	////Load tất cả các Map Object (Ground, Non-Ground,...).
	//std::ifstream inFile;
	//inFile.open(mapObjectPath);
	//if (!inFile)
	//	PrintDebug("MapObject file not exist ! \n");
	//std::string sInputString;

	//std::getline(inFile, sInputString);

	//std::istringstream iss(sInputString);

	//int numOfObject;

	//iss >> numOfObject;

	//Tag entityTag;

	//int objectID = -1;
	//int objectTopLeftX = -1;
	//int objectTopLeftY = -1;
	//int objectWidth = -1;
	//int objectHeight = -1;

	//for (int i = 0; i < numOfObject; ++i)
	//{
	//	std::getline(inFile, sInputString);
	//	std::istringstream iss(sInputString);
	//	iss >> objectID >> objectTopLeftX >> objectTopLeftY >> objectWidth >> objectHeight;
	//	if (objectID == 0)
	//		entityTag = Tag::ground;
	//	Entity* mapObject = new Entity();
	//	mapObject->SetTag(entityTag);
	//	mapObject->SetHeight(objectHeight);
	//	mapObject->SetWidth(objectWidth);
	//	mapObject->setPos(objectTopLeftX + (float)objectWidth/2, objectTopLeftY + (float)objectHeight/2);
	//	staticObject.push_back(mapObject);
	//}
}

std::vector<Object*> &GameMap::getStaticObject()
{
	return staticObject;
}

GameMap::~GameMap()
{
	if (camera != nullptr)
		camera->ReleaseCameraInstance();
	if (tMap != nullptr)
		delete tMap;
	for (int i = 0; i < staticObject.size(); ++i)
	{
		delete staticObject[i];
	}
	staticObject.clear();
}

void GameMap::Draw()
{
	//RECT srcRECT = camera->getCameraRECT();
	//D3DXVECTOR3 position(0, 0, 0);
	tMap->Draw(camera);
}

void GameMap::SetCamera(Camera* newCamera)
{

}
