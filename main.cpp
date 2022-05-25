#include "WinApp.h"
#include "Input.h"
#include "Graphics.h"
#include "IniDX.h"
#include "Draw.h"

WinApp* winApp = new WinApp;
Input* input = new Input;
Graphics* graphics = new Graphics;
IniDX* iniDX = new IniDX;
Draw* draw = new Draw;

//windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//ウィンドウ生成
	winApp->WinCreate();

	//初期化処理
	iniDX->Ini(winApp->hwnd);
	draw->Ini(iniDX);
	input->Ini(winApp->w, iniDX->result, winApp->hwnd);
	
	//毎フレーム処理
	winApp->MessageLoop(iniDX,draw,input,graphics);
	
	delete winApp;
	delete input;
	delete graphics;
	delete iniDX;
	delete draw;

	return 0;
}