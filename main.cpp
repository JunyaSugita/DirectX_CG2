#include <Windows.h>

//windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//コンソールへの文字入力
	OutputDebugStringA("Hello,DirectX!!\n");

	//ウィンドウサイズ
	const int window_width = 1280;
	const int window_height = 720;

	//ウインドウクラスの設定
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;		//ウインドウプロシージャの設定
	w.lpszClassName = L"DirectX";				//ウインドウクラス名
	w.hInstance = GetModuleHandle(nullptr);		//ウインドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW);	//カーソル指定

	//ウインドウクラスをOSに登録する
	RegisterClassEx(&w);
	//ウインドウサイズ{X,Y,横幅,縦幅}
	RECT wrc = { 0,0,window_width,window_height };
	//自動でサイズ補正
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	return 0;
}

//ウインドウプロシージャ
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
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

