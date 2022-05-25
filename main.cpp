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

//windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//�E�B���h�E����
	winApp->WinCreate();

	//����������
	iniDX->Ini(winApp->hwnd);
	draw->Ini(iniDX);
	input->Ini(winApp->w, iniDX->result, winApp->hwnd);
	
	//���t���[������
	winApp->MessageLoop(iniDX,draw,input,graphics);
	
	delete winApp;
	delete input;
	delete graphics;
	delete iniDX;
	delete draw;

	return 0;
}