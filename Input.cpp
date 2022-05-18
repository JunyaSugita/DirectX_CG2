#include "Input.h"

//�R���X�g���N�^
Input::Input(){}

//�f�X�g���N�^
Input::~Input(){}

//�֐�
void Input::Ini(WNDCLASSEX w, HRESULT result, HWND hwnd) {
	//DirectInput�̏�����
	directInput = nullptr;
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::GetKey(IniDX* iniDX) {
	keyboard->Acquire();
	//�S�L�[�̓��͏�Ԃ��擾����
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