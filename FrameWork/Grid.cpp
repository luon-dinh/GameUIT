#include "Grid.h"
#include <fstream>
#include <sstream>

Grid::Grid(long _mapWidth, long _mapHeight, const char * spawnPosition)
{
	mapWidth = _mapWidth;
	mapHeight = _mapHeight;

	gridWidth = mapWidth / cellSize + 1;
	gridHeight = mapHeight / cellSize + 1;

	//Khởi tạo danh sách các cells.
	cells = new std::list<Object*>*[gridHeight]; //Khởi tạo theo chiều dọc trước.
	for (int i = 0; i < gridHeight; ++i)
	{
		cells[i] = new std::list<Object*>[gridWidth];
	}

	//Khởi tạo danh sách một mảng 2 chiều.
	objectIDPerPosition = new int *[mapHeight];
	for (int i = 0; i < mapHeight; ++i)
		objectIDPerPosition[i] = new int[mapWidth];
	//Xoá sạch mảng (reset lại về 0).
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			objectIDPerPosition[i][j] = -1;
		}
	}
	LoadSpawnPosition(spawnPosition);
}

void Grid::LoadSpawnPosition(const char * spawnInfoFilePath)
{
	//Load tất cả các Dynamic Object (các object tương tác được).
	std::ifstream inFile;
	inFile.open(spawnInfoFilePath);
	if (!inFile)
		PrintDebug("Spawn Info File Path not found !");
	std::string sInputString;

	int objectID = -1;
	int objectTopLeftX = -1;
	int objectTopLeftY = -1;
	int objectWidth = -1;
	int objectHeight = -1;

	int numOfObject;

	std::getline(inFile, sInputString);
	std::istringstream iss(sInputString);
	iss >> numOfObject;

	for (int i = 0; i < numOfObject; ++i)
	{
		Object* object = nullptr;
		std::getline(inFile, sInputString);
		std::istringstream iss(sInputString);
		iss >> objectID >> objectTopLeftX >> objectTopLeftY >> objectWidth >> objectHeight;

		int midX = objectTopLeftX + objectWidth / 2;
		int midY = objectTopLeftY - objectHeight / 2;
		//Xét từng ID để xem nó là loại object động gì.
		objectIDPerPosition[midY][midX] = objectID;
		//Add object vô grid nào.
		if (objectID == ObjectID::ITEMLOOTER)
			object = new Container();

		if (object == nullptr)
			continue;

		object->pos.x = midX;
		object->pos.y = midY;
		Add(object);
	}
}

void Grid::KillAndDelAllObjectsInCell(int cellX, int cellY)
{
	std::list<Object*>& curList = cells[cellY][cellX];
	//Xoá tất cả các object hiện có trong cell này.
	//Đầu tiên ta phải vô hiệu hoá object.
	//Thực chất vô hiệu hoá object là việc xét xem object có được xoá khỏi grid hay không.

	//Nếu sau khi set Deactivated mà object vẫn còn Activated.
	//Chứng tỏ object còn đang hoạt động nên không delete.
	for (auto object : curList)
		object->DeactivateObject();
	for (auto it = curList.begin(); it != curList.end(); ++it)
	{
		//Nếu object hiện tại vẫn đang được kích hoạt thì ta bỏ qua.
		if ((*it)->GetActivatedStatus())
			continue;
		delete (*it);
		it = curList.erase(it);
		if (it == curList.end())
			break;
	}
}

void Grid::SpawnAllObjectsInCell(int cellX, int cellY)
{
	int fromX = cellX * cellSize;
	int toX = (cellX + 1)* cellSize;
	int fromY = cellY * cellSize;
	int toY = (cellY + 1) * cellSize;

	//Quét từ dưới lên, từ trái qua phải.
	for (int i = fromY; i < toY; ++i)
	{
		for (int j = fromX; j < toX; ++j)
		{
			//Nếu tại vị trí này không có object nào hết thì ta bỏ qua.
			if (objectIDPerPosition[i][j] < 0)
				continue;

			//Spawn (tạo mới) object dựa vào ID đã load sẵn.
			Object* newObject = nullptr;
			if (objectIDPerPosition[i][j] == ObjectID::ITEMLOOTER)
			{
				//ItemLooter không được sinh lần 2.
				//newObject = new Container(); //Tạo mới object dựa vào ID.
			}
			if (newObject == nullptr)
				continue;
			newObject->pos.x = j;
			newObject->pos.y = i;
			//Sau đó thêm nó vào GRID luôn.
			Add(newObject);
		}
	}
}

Grid::~Grid()
{
	//Xoá danh sách các cells.
	for (int i = 0; i < gridHeight; ++i)
	{
		for (int j = 0; j < gridWidth; ++j)
		{
			for (auto i : cells[i][j])
			{
				Player* testPlayer = dynamic_cast<Player*> (i);
				Shield* testShield = dynamic_cast<Shield*> (i);

				//Chỉ xoá khi không phải là player và shield.
				if (testPlayer != nullptr && testShield != nullptr)
					delete i;
			}
			cells[i][j].clear();
		}
		delete []cells[i];
	}
	delete cells;
	//Xoá danh sách các object.
	for (int i = 0; i < mapHeight; ++i)
		delete[]objectIDPerPosition[i];
	delete objectIDPerPosition;
}

void Grid::Add(Object* objectToAdd)
{
	int cellX = objectToAdd->pos.x / cellSize;
	int cellY = objectToAdd->pos.y / cellSize;

	//Sắp xếp vị trí để shield luôn luôn hiển thị trước mọi thứ khác.
	cells[cellY][cellX].push_front(objectToAdd);
}

void Grid::ActivateCells()
{
	RECT cameraRECT = Camera::getCameraInstance()->getCameraRECT();

	//Ta cần xem độ dời của activated grid là bao nhiêu để xét Respawn.

	int nextTopY;
	int nextBottomY;
	int nextRightX;
	int nextLeftX;

	nextTopY = cameraRECT.top / cellSize + 1;
	if (nextTopY >= gridHeight)
		nextTopY = gridHeight - 1;

	nextBottomY = cameraRECT.bottom / cellSize - 1;
	if (nextBottomY < 0)
		nextBottomY = 0;

	nextLeftX = cameraRECT.left / cellSize - 1;
	if (nextLeftX < 0)
		nextLeftX = 0;

	nextRightX = cameraRECT.right / cellSize + 1;
	if (nextRightX >= gridWidth)
		nextRightX = gridWidth - 1;

	//Xét respawn.
	//Xét respawn bên trái.
	for (int i = nextLeftX; i < leftX; ++i)
	{
		//Xét từ dưới lên theo khoảng dời.
		for (int j = nextBottomY; j < nextTopY; ++j)
		{
			//Respawn tất cả các object trong cell này.
			SpawnAllObjectsInCell(i, j);
		}
	}
	//Xét respawn bên phải.
	for (int i = rightX; i < nextRightX; ++i)
	{
		//Xét từ dưới lên theo khoảng dời.
		for (int j = nextBottomY; j < nextTopY; ++j)
		{
			//Respawn tất cả các object trong cell này.
			SpawnAllObjectsInCell(i, j);
		}
	}
	//Xét respawn bên trên.
	for (int i = topY; i < nextTopY; ++i)
	{
		for (int j = nextLeftX; j < nextRightX; ++j)
		{
			//Respawn tất cả các object trong cell này.
			SpawnAllObjectsInCell(j, i);
		}
	}

	//Xét respawn bên dưới.
	for (int i = nextBottomY; i < bottomY; ++i)
	{
		for (int j = nextLeftX; j < nextRightX; ++j)
		{
			//Respawn tất cả các object trong cell này.
			SpawnAllObjectsInCell(j, i);
		}
	}

	//Xét việc kill object bên trái.
	for (int i = leftX; i < nextLeftX; ++i)
	{
		for (int j = bottomY; j < topY; ++j)
		{
			KillAndDelAllObjectsInCell(i, j);
		}
	}

	//Xét việc kill object bên phải.
	for (int i = nextRightX; i < rightX; ++i)
	{
		for (int j = bottomY; j < topY; ++j)
		{
			KillAndDelAllObjectsInCell(i, j);
		}
	}
	
	//Xét việc kill object bên trên.
	for (int i = nextTopY; i < topY; ++i)
	{
		for (int j = leftX; j < rightX; ++j)
		{
			KillAndDelAllObjectsInCell(j, i);
		}
	}

	//Xét việc kill object bên dưới.
	for (int i = bottomY; i < nextBottomY; ++i)
	{
		for (int j = leftX; j < rightX; ++j)
		{
			KillAndDelAllObjectsInCell(j, i);
		}
	}

	//Gán lại các giá trị Active Zone theo giá trị mới.
	topY = nextTopY;
	bottomY = nextBottomY;
	leftX = nextLeftX;
	rightX = nextRightX;
}

void Grid::CollisionProcess()
{
	//Đầu tiên là ta xét collision với các object động với nhau.
	//Duyệt các cell.
	for (int i = bottomY; i <= topY; ++i)
	{
		for (int j = leftX; j <= rightX; ++j)
		{
			//Xét va chạm như trên trang web.

			//Chính mình.
			CollisionProcessCellToCell(j, i, j, i);

			//Cell trên đầu.
			if (i + 1 <= topY)
				CollisionProcessCellToCell(j, i, j, i + 1);
			//Cell góc trên trái.
			if (i + 1 <= topY && j - 1 >= 0)
				CollisionProcessCellToCell(j, i, j - 1, i + 1);
			//Cell góc bên trái.
			if (j - 1 >= 0)
				CollisionProcessCellToCell(j, i, j - 1, i);
			//Cell góc dưới trái.
			if (i - 1 >= 0 && j - 1 >= 0)
				CollisionProcessCellToCell(j, i, j - 1, i - 1);
		}
	}
}

void Grid::CollisionProcessCellToCell(int firstCellX, int firstCellY, int secondCellX, int secondCellY)
{
	std::list<Object*> &firstCell = cells[firstCellY][firstCellX];
	std::list<Object*> &secondCell = cells[secondCellY][secondCellX];

	//Duyệt qua các phần tử của cell đầu tiên.
	for (std::list<Object*>::iterator firstCellIt = firstCell.begin(); firstCellIt != firstCell.end(); ++firstCellIt)
	{
		BoundingBox firstCellObjBoundingBox = (*firstCellIt)->getBoundingBox();
		for (std::list<Object*>::iterator secondCellIt = secondCell.begin(); secondCellIt != secondCell.end(); ++secondCellIt)
		{
			//Không xét trường hợp tự va chạm với chính mình.
			if (*firstCellIt == *secondCellIt)
				continue;

			BoundingBox secondCellObjBoundingBox = (*secondCellIt)->getBoundingBox();

			//AABB.
			//bool collided = Collision::getInstance()->IsCollide(firstCellObjBoundingBox, secondCellObjBoundingBox);
			//if (collided)
			//{
			//	(*firstCellIt)->OnCollisionWithDynamicObject(*secondCellIt);
			//	(*secondCellIt)->OnCollisionWithDynamicObject(*firstCellIt);
			//}

			//Swept AABB.
			collisionOut firstObjColOut = Collision::getInstance()->SweptAABB(firstCellObjBoundingBox, secondCellObjBoundingBox);

			collisionOut secondObjColOut;
			secondObjColOut.collisionTime = firstObjColOut.collisionTime;
			
			//Nếu không có va chạm xảy ra.
			if (firstObjColOut.side == CollisionSide::none)
				continue;

			//Hướng va chạm ngược so với object kia.
			if (firstObjColOut.side == CollisionSide::left)
				secondObjColOut.side = CollisionSide::right;

			else if (firstObjColOut.side == CollisionSide::bottom)
				secondObjColOut.side = CollisionSide::top;

			else if (firstObjColOut.side == CollisionSide::top)
				secondObjColOut.side = CollisionSide::bottom;

			else if (firstObjColOut.side == CollisionSide::right)
				secondObjColOut.side = CollisionSide::left;

			else
				secondObjColOut.side = firstObjColOut.side;

			//Xử lý va chạm giữa 2 object với nhau.
			(*firstCellIt)->OnCollision(*secondCellIt, &firstObjColOut);
			(*secondCellIt)->OnCollision(*firstCellIt, &secondObjColOut);
		}
	}
}

void Grid::UpdateActivatedCells(double dt)
{
	//Duyệt từ dưới lên trước, sau đó duyệt từ trái qua phải.
	for (int i = bottomY; i <= topY; ++i)
	{
		int cellY = i;
		for (int j = leftX; j <= rightX; ++j)
		{
			int cellX = j;
			std::list<Object*>::iterator it = cells[i][j].begin();
			while (it != cells[i][j].end())
			{
				//Duyệt hết các phần tử có trong cells này.
				//Kiểm tra xem có sự thay đổi cells của các object hay không.
				//Lưu lại thông tin của object hiện tại.
				(*it)->Update(dt);
				it = MoveObjectAndIncrementIterator(cellX, cellY, it, (*it)); //Lúc này là đã di chuyển luôn iterator rồi.
			}
		}
	}
	
}

std::list<Object*>::iterator Grid::MoveObjectAndIncrementIterator(int cellX, int cellY, std::list<Object*>::iterator it, Object* object)
{
	//Kiểm tra xem object sau khi di chuyển còn thuộc cell hiện tại hay không.
	int nextCellX = object->pos.x / cellSize;
	int nextCellY = object->pos.y / cellSize;
	if (cellX == nextCellX && cellY == nextCellY)
		return (++it);

	//Thực hiện việc di chuyển qua cell khác.

	//Xoá object ở cell cũ.
	if (it != cells[cellY][cellX].end())
		cells[cellY][cellX].erase(it++);
	else
		cells[cellY][cellX].erase(it--);

	//Thêm object vào cell mới.
	Add(object);
	return it;
}

void Grid::RenderActivatedCells()
{
	//Vẽ tất cả các cells được activated.
	for (int i = bottomY; i <= topY; ++i)
	{
		for (int j = leftX; j <= rightX; ++j)
		{
			//Vẽ tất cả các object có trong cell.
			for (auto object : cells[i][j])
			{
				Container* itemLooter = dynamic_cast<Container*> (object);
				if (itemLooter != nullptr)
				{
					int a = 10;
				}
				object->RenderInGrid();
			}
		}
	}
	DrawDebugObject();
}

void Grid::DrawDebugObject()
{
	//Vẽ tất cả các object động.
	//Duyệt qua tất cả các cell.
	for (int i = 0; i < gridHeight; ++i)
	{
		for (int j = 0; j < gridWidth; ++j)
		{
			for (auto object : cells[i][j])
			{
				DrawDebug::DrawBoundingBox(object->getBoundingBox(), Tag::TESTMAPOBJECTRED);
			}
		}
	}
}

