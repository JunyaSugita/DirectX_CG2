#include "WinApp.h"

WinApp::WinApp() {
}

WinApp::~WinApp() {
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

void WinApp::MessageLoop(IniDX* iniDX, Draw* draw, Input* input, Graphics* graphics) {
	//ゲームループ
	while (true) {
		//メッセージがあるか?
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);	//キー入力メッセージの処理
			DispatchMessage(&msg);	//プロシージャにメッセージを送る
		}
		graphics->Process(iniDX, draw);
		input->GetKey(iniDX);

		switch (changeColor)
		{
		case 0:
			r += 0.01f;
			if (r >= 1.0f) {
				changeColor++;
			}
			break;
		case 1:
			b -= 0.01f;
			if (b <= 0.0f) {
				changeColor++;
			}
			break;
		case 2:
			g += 0.01f;
			if (g >= 1.0f) {
				changeColor++;
			}
			break;
		case 3:
			r -= 0.01f;
			if (r <= 0.0f) {
				changeColor++;
			}
			break;
		case 4:
			b += 0.01f;
			if (b >= 1.0f) {
				changeColor++;
			}
			break;
		case 5:
			g -= 0.01f;
			if (g <= 0.0f) {
				changeColor = 0;
			}
			break;
		default:
			break;
		}

		if (input->key[DIK_SPACE]) {
			a = 0.2f;
		}
		else {
			a = 1.0f;
		}


		draw->constMapMaterial->color = XMFLOAT4(r, g, b, a);

		if (input->key[DIK_D] || input->key[DIK_A]) {
			if (input->key[DIK_D]) {
				angle -= XMConvertToRadians(1.0f);
			}
			else if (input->key[DIK_A]) {
				angle += XMConvertToRadians(1.0f);
			}

			draw->eye.x = -100 * sinf(angle);
			draw->eye.z = -100 * cosf(angle);
			draw->matView = XMMatrixLookAtLH(XMLoadFloat3(&draw->eye), XMLoadFloat3(&draw->target), XMLoadFloat3(&draw->up));
		}
		draw->position = { 0.0f,0.0f,0.0f };


		if (input->key[DIK_UP] || input->key[DIK_DOWN] || input->key[DIK_RIGHT] || input->key[DIK_LEFT]) {
			if (input->key[DIK_UP]) { draw->object3ds[0].worldTransform.trans.y += 1.0f; }
			if (input->key[DIK_DOWN]) { draw->object3ds[0].worldTransform.trans.y -= 1.0f; }
			if (input->key[DIK_RIGHT]) { draw->object3ds[0].worldTransform.trans.x += 1.0f; }
			if (input->key[DIK_LEFT]) { draw->object3ds[0].worldTransform.trans.x -= 1.0f; }
		}

		if (input->key[DIK_Q] || input->key[DIK_E]) {
			if (input->key[DIK_Q]) { draw->object3ds[0].worldTransform.rotation.y += 0.02f; }
			if (input->key[DIK_E]) { draw->object3ds[0].worldTransform.rotation.y -= 0.02f; }
		}

		if (input->key[DIK_W] || input->key[DIK_S]) {

			if (input->key[DIK_W]) { draw->object3ds[0].worldTransform.scale += {0.02f, 0.02f, 0.02f}; }
			if (input->key[DIK_S]) { draw->object3ds[0].worldTransform.scale -= {0.02f, 0.02f, 0.02f}; }
			if (draw->object3ds[0].worldTransform.scale.x < 0) {
				draw->object3ds[0].worldTransform.scale += {0.02f, 0.02f, 0.02f};
			}
		}

		if (input->key[DIK_1] && input->oldKey[DIK_1] == 0) {
			if (graphics->solid == false) {
				graphics->solid = true;
			}
			else {
				graphics->solid = false;
			}
		}

		if ((input->key[DIK_2] && input->oldKey[DIK_2] == 0)) {
			type++;
			if (type > 3) {
				type = 0;
			}
		}

		graphics->triangle = false;
		graphics->model3d = false;
		graphics->circle = false;
		switch (type)
		{
		case 0:
			graphics->triangle = true;
			break;
		case 1:
			graphics->triangle = false;
			break;
		case 2:
			graphics->model3d = true;
			break;
		case 3:
			graphics->circle = true;
			break;
		default:
			break;
		}


		for (int i = 0; i < _countof(draw->object3ds); i++) {
			draw->object3ds[i].UpdateObject3d();
			XMMATRIX XMMatWorld;
			XMMatWorld =
			{
				draw->object3ds[i].worldTransform.matWorld.m[0][0],draw->object3ds[i].worldTransform.matWorld.m[0][1],draw->object3ds[i].worldTransform.matWorld.m[0][2],draw->object3ds[i].worldTransform.matWorld.m[0][3],
				draw->object3ds[i].worldTransform.matWorld.m[1][0],draw->object3ds[i].worldTransform.matWorld.m[1][1],draw->object3ds[i].worldTransform.matWorld.m[1][2],draw->object3ds[i].worldTransform.matWorld.m[1][3],
				draw->object3ds[i].worldTransform.matWorld.m[2][0],draw->object3ds[i].worldTransform.matWorld.m[2][1],draw->object3ds[i].worldTransform.matWorld.m[2][2],draw->object3ds[i].worldTransform.matWorld.m[2][3],
				draw->object3ds[i].worldTransform.matWorld.m[3][0],draw->object3ds[i].worldTransform.matWorld.m[3][1],draw->object3ds[i].worldTransform.matWorld.m[3][2],draw->object3ds[i].worldTransform.matWorld.m[3][3],
			};

			draw->object3ds[i].constMapTransform->mat = XMMatWorld * draw->matView * draw->matProjection;
		}

		//×ボタンで終了
		if (msg.message == WM_QUIT) {
			break;
		}
	}

	//ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}