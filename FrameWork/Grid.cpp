#include "Grid.h"

Grid::Grid(int mapWidth, int mapHeight)
{
	gridWidth = mapWidth / cellSize + 1;
	gridHeight = mapHeight / cellSize + 1;

	//Khởi tạo danh sách các cells.
	cells = new std::list<Object*>*[gridHeight]; //Khởi tạo theo chiều dọc trước.
	for (int i = 0; i < gridHeight; ++i)
	{
		cells[i] = new std::list<Object*>[gridWidth];
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
				delete i;
			cells[i][j].clear();
		}
		delete cells[i];
	}
	delete cells;
}

void Grid::Add(Object* objectToAdd)
{
	int cellX = objectToAdd->pos.x / cellSize;
	int cellY = objectToAdd->pos.y / cellSize;
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
		for (int j = nextBottomY; j <= nextTopY; ++j)
		{
			//Respawn tất cả các object trong cell này.
			for (auto object : cells[j][i])
			{
				object->Respawn();
			}
		}
	}
	//Xét respawn bên phải.
	for (int i = nextRightX; i > rightX; --i)
	{
		//Xét từ dưới lên theo khoảng dời.
		for (int j = nextBottomY; j <= nextTopY; ++j)
		{
			//Respawn tất cả các object trong cell này.
			for (auto object : cells[j][i])
			{
				object->Respawn();
			}
		}
	}
	//Xét respawn bên trên.
	for (int i = nextTopY; i > topY; --i)
	{
		for (int j = nextLeftX; j <= nextRightX; ++j)
		{
			for (auto object : cells[i][j])
				object->Respawn();
		}
	}

	//Xét respawn bên dưới.
	for (int i = nextBottomY; i < bottomY; ++i)
	{
		for (int j = nextLeftX; j <= nextRightX; ++j)
		{
			for (auto object : cells[i][j])
				object->Respawn();
		}
	}
}

void Grid::CollisionProcess()
{
	//Đầu tiên là ta xét collision với các object động với nhau.
	//Duyệt các cell.
	for (int i = bottomY; i <= topY; ++i)
	{
		for (int j = leftX; i <= rightX; ++j)
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

	//Sau đó ta xét việc va chạm với các object tĩnh (Map object).

}

void Grid::CollisionProcessCellToCell(int firstCellX, int firstCellY, int secondCellX, int secondCellY)
{
	std::list<Object*> * firstCell = &cells[firstCellY][firstCellX];
	std::list<Object*> * secondCell = &cells[secondCellY][secondCellX];

	//Duyệt qua các phần tử của cell đầu tiên.
	for (std::list<Object*>::iterator firstCellIt = firstCell->begin(); firstCellIt != firstCell->end(); ++firstCellIt)
	{
		BoundingBox firstCellObjBoundingBox = (*firstCellIt)->getBoundingBox();
		for (std::list<Object*>::iterator secondCellIt = secondCell->begin(); secondCellIt != secondCell->end(); ++secondCellIt)
		{
			BoundingBox secondCellObjBoundingBox = (*secondCellIt)->getBoundingBox();
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
			(*firstCellIt)->OnCollision((*secondCellIt), &firstObjColOut);
			(*secondCellIt)->OnCollision((*firstCellIt),&secondObjColOut);
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
			//Duyệt hết các phần tử có trong cells này.
			for (std::list<Object*>::iterator it = cells[i][j].begin(); it != cells[i][j].end(); ++it)
			{
				//Kiểm tra xem có sự thay đổi cells của các object hay không.
				//Lưu lại thông tin của object hiện tại.
				(*it)->Update(dt);
				it = MoveObject(cellX, cellY, it, (*it));
			}
		}
	}
	
}

std::list<Object*>::iterator Grid::MoveObject(int cellX, int cellY, std::list<Object*>::iterator it, Object* object)
{
	//Kiểm tra xem object sau khi di chuyển còn thuộc cell hiện tại hay không.
	int nextCellX = object->pos.x / cellSize;
	int nextCellY = object->pos.y / cellSize;
	if (cellX == nextCellX && cellY == nextCellY)
		return it;

	//Thực hiện việc di chuyển qua cell khác.

	//Xoá object ở cell cũ.
	cells[cellY][cellX].erase(it++);

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
				object->Render();
			}
		}
	}
}

