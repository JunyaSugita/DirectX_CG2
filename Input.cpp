#include "Input.h"

//コンストラクタ
Input::Input(){}

//デストラクタ
Input::~Input(){}

//関数
void Input::Ini(WNDCLASSEX w, HRESULT result, HWND hwnd) {
	//DirectInputの初期化
	directInput = nullptr;
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::GetKey(IniDX* iniDX) {
	keyboard->Acquire();
	//全キーの入力状態を取得する
	BYTE key[256] = {};
	iniDX->result = keyboard->GetDeviceState(sizeof(key), key);
	assert(SUCCEEDED(iniDX->result));

	float color;
	if (key[DIK_SPACE]) {
		color = 0.9f;
	}
	else {
		color = 0.1f;
	}
}