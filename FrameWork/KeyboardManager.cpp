#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::instance = NULL;

KeyboardManager::KeyboardManager()
{
}


KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Create(HINSTANCE hInstance,HWND hwnd)
{
	HRESULT hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&this->di8,
		NULL);
	if (FAILED(hr))
		MessageBox(NULL, "Key", "Err", MB_OK);
	hr = this->di8->CreateDevice(GUID_SysKeyboard, &this->did8, NULL);
	if (FAILED(hr))
		MessageBox(NULL, "Key", "Err", MB_OK);
	hr = this->did8->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		MessageBox(NULL, "Key", "Err", MB_OK);
	hr = this->did8->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
		MessageBox(NULL, "Key", "Err", MB_OK);
	hr = this->did8->Acquire();
	if (FAILED(hr))
		MessageBox(NULL, "Key", "Err", MB_OK);
}

KeyboardManager* KeyboardManager::getInstance()
{
	if (!instance)
		instance = new KeyboardManager();
	return instance;
}

void KeyboardManager::getState(double dt)
{
	HRESULT hr = this->did8->GetDeviceState(sizeof(this->key_buffer), (LPVOID)&this->key_buffer);
	if (FAILED(hr))
	{
		while (this->did8->Acquire() == DIERR_INPUTLOST);
		this->did8->GetDeviceState(sizeof(this->key_buffer), (LPVOID)&this->key_buffer);
	}

	//Xét trạng thái để dùng cho hàm kiểm tra click một lần.
	for (int i = 0; i < 256; ++i)
	{
		//Đầu tiên ta gán activatedKeys (những phím được nhấn trong vòng lặp này).
		activatedKeys[i] = key_buffer[i] & 0x80;

		//Đây là đoạn code dùng để xét click một lần.
		if (activatedKeys[i]) //Nếu phím đang được click.
		{
			//Xét xem trước đó phím đã được click chưa.
			if (prevClicked[i]) //Nếu trước đó đã được click thì là giữ đè nên = false.
				clickedKeys[i] = false;
			else //Nếu trước đó chưa được click thì đây là lần click đầu tiên.
				clickedKeys[i] = true;

			//Lần click bây giờ đã trở thành quá khứ.
			prevClicked[i] = true;
		}
		else
		{
			clickedKeys[i] = false;
			prevClicked[i] = false;
		}
	}

	//Cập nhật thời gian click.
	//Xét nếu phím đã nhả ra thì ta reset lại thời gian click về = 0.
	//Nếu phím đang được ấn thì cập nhật lại dt.
	for (int i = 0; i < 256; ++i)
	{
		if (!activatedKeys[i]) //Nếu phím không được ấn.
			timeSinceLastClicked[i] = -1;
		else if (activatedKeys[i] && clickedKeys[i]) //Nếu phím đang được ấn và hiện tại là lần click đầu tiên.
			timeSinceLastClicked[i] = 0;
		else if (activatedKeys[i] && !clickedKeys[i]) //Nếu đây là frame thứ 2 sau khi click thì ta mới cập nhật thời gian.
			timeSinceLastClicked[i] += dt;
	}
}

bool KeyboardManager::isKeyDown(int key)
{
	return key_buffer[key] && 0x80;
}

bool KeyboardManager::getKeyPressedOnce(int key)
{
	return clickedKeys[key];
}

bool KeyboardManager::getKeyPressedOnce(int key, int& timeSinceLastPressed)
{
	//Ta gán thời gian.
	timeSinceLastPressed = timeSinceLastClicked[key];
	//Trả về clicked.
	return clickedKeys[key];
}

bool KeyboardManager::isKeyUp(int key)
{
	return !(key_buffer[key] && 0x80);
}