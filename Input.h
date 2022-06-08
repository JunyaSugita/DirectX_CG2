#pragma once
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <assert.h>
#include "IniDX.h"

class Input{
public:
	Input();
	~Input();

//�����o�֐�
public:
	void Ini(WNDCLASSEX w, HRESULT result, HWND hwnd);
	void GetKey(IniDX* iniDX);

//�����o�ϐ�
public:
	IDirectInput8* directInput;
	IDirectInputDevice8* keyboard;

};





