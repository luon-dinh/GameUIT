#pragma once
#include <list>
#include "Object.h"
#include "Collision.h"
#include "Camera.h"

//Phải gọi hàm ActivateCells() trước khi làm bất kỳ thứ gì khác.
class Grid // lam singleton
{
	//Danh sách các object được tổ chức dưới dạng 2 chiều (từng cell) và trong các cell chứa các Unit.
	std::list<Object*> ** cells;
	const int cellSize = 80;
	int gridWidth;
	int gridHeight;

	//Vùng mà grid được activated.
	int topY;
	int bottomY;
	int leftX;
	int rightX;

	//Hàm dùng để di chuyển một object từ cell này sang cell khác.

public:
	Grid(int mapWidth, int mapHeight);
	~Grid();
	void Add(Object *); //Thêm object vào grid dựa vào toạ độ của object.
	void ActivateCells(); //Activate những vùng sẽ được xử lý bởi Grid (vùng được khoanh bởi Camera).

	//Nhớ kiểm tra va chạm trước khi Update.
	void CollisionProcess();
	void UpdateActivatedCells(double dt);
	void RenderActivatedCells();
private:
	std::list<Object*>::iterator MoveObject(int currentCellX, int currentCellY, std::list<Object*>::iterator, Object*);
	void CollisionProcessCellToCell(int firstCellX, int firstCellY, int secondCellX, int secondCellY);
};