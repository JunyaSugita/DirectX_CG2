#pragma once

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <assert.h>

class Input{
public:
	Input();
	~Input();

//�����o�֐�
public:
	void Initialize(WNDCLASSEX w, HRESULT result, HWND hwnd);

//�����o�ϐ�
public:
	IDirectInput8* directInput;
	IDirectInputDevice8* keyboard;

};

