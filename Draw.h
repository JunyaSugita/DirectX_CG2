#pragma once
#include "IniDX.h"
#include <DirectXMath.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

struct Vertex {
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

class Draw{
public:
	Draw();
	~Draw();

public:
	void Ini(IniDX* iniDX);

	void ConstBaffer(IniDX* iniDX);

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	ID3D12PipelineState* pipelineState;
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};
	//���\�[�X�ݒ�
	ID3D12Resource* constBuffMaterial = nullptr;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// �F (RGBA)
	};
	//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		XMMATRIX mat;		// 3D�ϊ��s��
	};

	ID3D12Resource* constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//�F
	ConstBufferDataMaterial* constMapMaterial;

	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//�J�����֌W
	XMMATRIX matview;
	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;

	XMMATRIX matProjection;
};

