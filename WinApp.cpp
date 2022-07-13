#include "WinApp.h"

WinApp::WinApp() {
}

WinApp::~WinApp(){
}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの修了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::WinCreate() {
	//ウインドウクラスの設定
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;		//ウインドウプロシージャの設定
	w.lpszClassName = L"DirectXGame";			//ウインドウクラス名
	w.hInstance = GetModuleHandle(nullptr);		//ウインドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW);	//カーソル指定

	//ウインドウクラスをOSに登録する
	RegisterClassEx(&w);
	//ウインドウサイズ{X,Y,横幅,縦幅}
	RECT wrc = { 0,0,window_width,window_height };
	//自動でサイズ補正
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(
		w.lpszClassName,		//クラス名
		L"DirectXGame",			//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	//標準的なウィンドウスタイル
		CW_USEDEFAULT,			//表示X座標(OSに任せる)
		CW_USEDEFAULT,			//表示Y座標(OSに任せる)
		wrc.right - wrc.left,	//ウィンドウ横幅
		wrc.bottom - wrc.top,	//ウィンドウ縦幅
		nullptr,				//親ウィンドウハンドル
		nullptr,				//メニューハンドル
		w.hInstance,			//呼び出しアプリケーションハンドル
		nullptr					//オプション
	);

	//ウインドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::MessageLoop(IniDX *iniDX, Draw* draw, Input* input, Graphics* graphics) {
	//ゲームループ
	while (true) {
		//メッセージがあるか?
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);	//キー入力メッセージの処理
			DispatchMessage(&msg);	//プロシージャにメッセージを送る
		}
		graphics->Process(iniDX, draw);
		input->GetKey(iniDX);

		a += 0.01f;
		if (a >= 1.0f) {
			a = 1.0f;
		}
		draw->constMapMaterial->color = XMFLOAT4(1-a,a,0,1);

		if (input->key[DIK_D] || input->key[DIK_A]) {
			if (input->key[DIK_D]) {
				angle += XMConvertToRadians(1.0f);
			}
			else if (input->key[DIK_A]) {
				angle -= XMConvertToRadians(1.0f);
			}

			draw->eye.x = -100 * sinf(angle);
			draw->eye.z = -100 * cosf(angle);
			draw->matview = XMMatrixLookAtLH(XMLoadFloat3(&draw->eye), XMLoadFloat3(&draw->target), XMLoadFloat3(&draw->up));
		}
		draw->position = { 0.0f,0.0f,0.0f };

		if (input->key[DIK_UP] || input->key[DIK_DOWN] || input->key[DIK_RIGHT] || input->key[DIK_LEFT]) {
			if (input->key[DIK_UP]) {
				draw->position.y += 1.0f;
			}
			else if (input->key[DIK_DOWN]) {
				draw->position.y -= 1.0f;
			}
			if (input->key[DIK_RIGHT]) {
				draw->position.x += 1.0f;
			}
			else if (input->key[DIK_LEFT]) {
				draw->position.x -= 1.0f;
			}
		}

		XMMATRIX matTrans;
		matTrans = XMMatrixTranslation(draw->position.x, draw->position.y, draw->position.z);
		draw->matWorld *= matTrans;

		//定数バッファに転送
		//draw->constMapTransform0->mat = draw->matWorld * draw->matview * draw->matProjection;
		//draw->constMapTransform1->mat = draw->matWorld1 * draw->matview * draw->matProjection;


		//×ボタンで終了
		if (msg.message == WM_QUIT) {
			break;
		}
	}

	//ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}