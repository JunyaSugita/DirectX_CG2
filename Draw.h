#pragma once
#include "IniDX.h"
#include <DirectXMath.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

class Draw{
public:
	Draw();
	~Draw();

public:
	void Ini(IniDX* iniDX);

public:
	std::vector<XMFLOAT3> vertices;
	std::vector<uint16_t> indices;

	ID3D12PipelineState* pipelineState;
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParam = {};
	//���\�[�X�ݒ�
	ID3D12Resource* constBuffMaterial = nullptr;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// �F (RGBA)
	};
	//�F
	ConstBufferDataMaterial* constMapMaterial;
};

