#include "GameMap.h"
#include <fstream>
#include <sstream>

GameMap::GameMap(const char * _imgPath, const char * _txtPath, const char * _mapObjectPath, MapName map)
{
	this->imgPath = _imgPath;
	this->txtPath = _txtPath;
	this->mapObjectPath = _mapObjectPath;

	if (map == MapName::CHARLES)
		tMap = new MapCharles(imgPath, txtPath);
	else if (map == MapName::CHARLESBOSSLIGHT)
		tMap = new MapCharlesBoss(imgPath, txtPath, Tag::MAPCHARLESBOSSLIGHT);
	else if (map == MapName::CHARLESBOSSDARK)
		tMap = new MapCharlesBoss(imgPath, txtPath, Tag::MAPCHARLESBOSSDARK);
	else if (map == MapName::PITTSBURGHLIGHT)
		tMap = new MapPittsburgh(imgPath, txtPath, Tag::MAPPITTSBURGHLIGHT);
	else if (map == MapName::PITTSBURGHDARK)
		tMap = new MapPittsburgh(imgPath, txtPath, Tag::MAPPITTSBURGHDARK);
	else if (map == MapName::PITTSBURGHPORTAL1DARK)
		tMap = new MapPittsburghPortal01(imgPath, txtPath, Tag::MAPPITTSBURGHPORTAL1DARK);
	else if (map == MapName::PITTSBURGHPORTAL1LIGHT)
		tMap = new MapPittsburghPortal01(imgPath, txtPath, Tag::MAPPITTSBURGHPORTAL1LIGHT);
	else if (map == MapName::PITTSBURGHPORTAL2LIGHT)
		tMap = new MapPittsburghPortal02(imgPath, txtPath, Tag::MAPPITTSBURGHPORTAL2LIGHT);
	else if (map == MapName::PITTSBURGHPORTAL2DARK)
		tMap = new MapPittsburghPortal02(imgPath, txtPath, Tag::MAPPITTSBURGHPORTAL2DARK);

	camera = Camera::getCameraInstance();

	mapHeight = tMap->GetMapHeight();
	mapWidth = tMap->GetMapWidth();

	//Load tất cả những đối tượng liên quan đến map như Ground, Animation,..
	LoadMapObject();
}

void GameMap::Update(double dt)
{
	tMap->Update(dt);
}

void GameMap::LoadMapObject()
{
	//Load tất cả các Map Object (Ground, Non-Ground,...).
	std::ifstream inFile;
	inFile.open(mapObjectPath);
	if (!inFile)
		PrintDebug("MapObject file not exist ! \n");
	std::string sInputString;

	std::getline(inFile, sInputString);

	std::istringstream iss(sInputString);

	int numOfObject;

	iss >> numOfObject;

	Type entityTag = Type::NONE;

	int objectID = -1;
	int objectTopLeftX = -1;
	int objectTopLeftY = -1;
	int objectWidth = -1;
	int objectHeight = -1;

	for (int i = 0; i < numOfObject; ++i)
	{
		std::getline(inFile, sInputString);
		std::istringstream iss(sInputString);

		//Xét từng ID để xem entityTag của nó là gì.
		if (objectID == 0)
			entityTag = Type::GROUND;
		else if (objectID == 1)
			entityTag = Type::SOLIDBOX;
		else if (objectID == 2)
			entityTag = Type::WATERRL;
		else if (objectID == 3)
			entityTag == Type::ROPE;
		else if (objectID == 4)
			entityTag == Type::ONOFF;

		Object* mapObject = new Object();
		mapObject->type = entityTag;
		mapObject->height = objectHeight;
		mapObject->width = objectWidth;
		mapObject->pos.x = objectTopLeftX + (float)objectWidth / 2;
		mapObject->pos.y = objectTopLeftY - (float)objectHeight / 2;
		staticObject.push_back(mapObject);
	}
}

std::vector<Object*> &GameMap::getStaticObject()
{
	return staticObject;
}

GameMap::~GameMap()
{
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
