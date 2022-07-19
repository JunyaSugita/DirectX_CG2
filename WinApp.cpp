#include "WinApp.h"

WinApp::WinApp() {
	isStart = false;
	model3d = false;
}

WinApp::~WinApp() {
}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg) {
		//�E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂��āA�A�v���̏C����`����
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::WinCreate() {
	//�E�C���h�E�N���X�̐ݒ�
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;		//�E�C���h�E�v���V�[�W���̐ݒ�
	w.lpszClassName = L"DirectXGame";			//�E�C���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);		//�E�C���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	//�E�C���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w);
	//�E�C���h�E�T�C�Y{X,Y,����,�c��}
	RECT wrc = { 0,0,window_width,window_height };
	//�����ŃT�C�Y�␳
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(
		w.lpszClassName,		//�N���X��
		L"DirectXGame",			//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,			//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,	//�E�B���h�E����
		wrc.bottom - wrc.top,	//�E�B���h�E�c��
		nullptr,				//�e�E�B���h�E�n���h��
		nullptr,				//���j���[�n���h��
		w.hInstance,			//�Ăяo���A�v���P�[�V�����n���h��
		nullptr					//�I�v�V����
	);

	//�E�C���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::MessageLoop(IniDX* iniDX, Draw* draw, Input* input, Graphics* graphics) {
	//�Q�[�����[�v
	while (true) {
		//���b�Z�[�W�����邩?
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);	//�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&msg);	//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
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
				angle += XMConvertToRadians(1.0f);
			}
			else if (input->key[DIK_A]) {
				angle -= XMConvertToRadians(1.0f);
			}

			draw->eye.x = -100 * sinf(angle);
			draw->eye.z = -100 * cosf(angle);
			draw->matView = XMMatrixLookAtLH(XMLoadFloat3(&draw->eye), XMLoadFloat3(&draw->target), XMLoadFloat3(&draw->up));
		}
		if (input->key[DIK_W] || input->key[DIK_S]) {
			if (input->key[DIK_W]) {
				angle += XMConvertToRadians(1.0f);
			}
			else if (input->key[DIK_S]) {
				angle -= XMConvertToRadians(1.0f);
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

		if (input->key[DIK_1] && input->oldKey[DIK_1] == 0) {
			if (graphics->solid == false) {
				graphics->solid = true;
			}
			else {
				graphics->solid = false;
			}
		}

		if ((input->key[DIK_2] && input->oldKey[DIK_2] == 0) || isStart == false) {
			if (graphics->triangle == true) {
				graphics->triangle = false;
				model3d = false;
				draw->indices = std::vector<uint16_t>(
					{
					0,1,2,
					1,2,3
					});
			}
			else {
				graphics->triangle = true;
				draw->indices = std::vector<uint16_t>(
					{
					0,1,2,
					});
				isStart = true;
			}
		}

		if ((input->key[DIK_3] && input->oldKey[DIK_3] == 0)) {
			if (model3d == false) {
				graphics->triangle = false;
				model3d = true;
				draw->indices = std::vector<uint16_t>(
					{
					//�O
					0,1,2,
					1,2,3,
					//��
					5,4,6,
					7,5,6,
					//��
					8,9,10,
					9,10,11,
					//�E
					13,12,14,
					15,13,14,
					//��
					17,16,18,
					19,17,18,
					//��
					20,21,22,
					21,22,23,
					}
				);
			}
			else {
				model3d = false;
				graphics->triangle = false;
				draw->indices = std::vector<uint16_t>(
					{
					0,1,2,
					}
				);
			}
		}

		if ((input->key[DIK_4] && input->oldKey[DIK_4] == 0)) {
			if (graphics->circle == false) {
				graphics->circle = true;
				graphics->triangle = true;
				draw->indices = std::vector<uint16_t>(
					{
						//�O
						0,1,2,
						1,2,3,
						//��
						5,4,6,
						7,5,6,
						//��
						8,9,10,
						9,10,11,
						//�E
						13,12,14,
						15,13,14,
						//��
						17,16,18,
						19,17,18,
						//��
						20,21,22,
						21,22,23,

						24,25,26,
						24,26,27,
						24,27,28,
						24,28,29,
						24,29,30,
						24,30,31,
						24,31,32,
						24,32,33,
						24,33,34,
						24,34,35,
						24,35,36,
						24,36,37,
						24,37,38,
						24,38,39,
						24,39,40,
						24,40,41,
						24,41,42,
						24,42,43,
						24,43,44,
						24,44,25,
					}
				);
			}
			else {
				graphics->circle = false;
				graphics->triangle = false;
				draw->indices = std::vector<uint16_t>(
					{
					0,1,2,
					}
				);
			}
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

		//�~�{�^���ŏI��
		if (msg.message == WM_QUIT) {
			break;
		}
	}

	//�E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}