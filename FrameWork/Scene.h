#pragma once

//Đây là một class đại diện cho một Scene nói chung. Class này chủ yếu được dùng để cho các lớp khác kế thừa từ nó.
class Scene
{
public:
	//Hàm này dùng để cập nhật Scene (VD Scene có các vật thể chuyển động theo thời gian,...).
	virtual void Update(double dt) {};

	//Hàm này dùng để load toàn bộ nội dung của một Scene (bao gồm các đối tượng của Scene, Scene Map,...).
	virtual void LoadContent() {};

	//Hàm này dùng để vẽ một Scene lên màn hình.
	virtual void Draw() {};

protected:
	Scene();
private:
};