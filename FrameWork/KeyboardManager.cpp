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

void KeyboardManager::getState()
{
	HRESULT hr = this->did8->GetDeviceState(sizeof(this->key_buffer), (LPVOID)&this->key_buffer);
	if (FAILED(hr))
	{
		while (this->did8->Acquire() == DIERR_INPUTLOST);
	}
}

bool KeyboardManager::isKeyDown(int key)
{
	return key_buffer[key] && 0x80;
}
