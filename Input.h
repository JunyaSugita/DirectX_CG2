#pragma once

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#define DIRECTINPUT_VERSION 0x0800 //DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <assert.h>

class Input{
public:
	Input();
	~Input();

//メンバ関数
public:
	void Initialize(WNDCLASSEX w, HRESULT result, HWND hwnd);

//メンバ変数
public:
	IDirectInput8* directInput;
	IDirectInputDevice8* keyboard;

};

