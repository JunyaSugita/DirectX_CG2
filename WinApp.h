#pragma once
#include "Graphics.h"
#include "input.h"
#include <DirectXTex.h>

class WinApp{
public:
	WinApp();
	~WinApp();
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void WinCreate();
	void MessageLoop(IniDX* iniDX, Draw* draw, Input* input, Graphics* graphics);

public:
	static const int window_width = 1280;
	static const int window_height = 720;
	WNDCLASSEX w{};
	HWND hwnd;
	MSG msg{};

	float a = 0.0f;
	float angle = 0.0f;


};

