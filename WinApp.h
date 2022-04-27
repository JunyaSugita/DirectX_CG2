#pragma once
#include <Windows.h>

class WinApp{
public:
	WinApp();
	~WinApp();
public:
	void WinCreate();
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	const int window_width = 1280;
	const int window_height = 720;
	WNDCLASSEX w{};
	HWND hwnd;
};

