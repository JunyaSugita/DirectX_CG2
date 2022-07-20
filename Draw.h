#pragma once
#include "IniDX.h"
#include <DirectXMath.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include "Object3d.h"

struct Vertex {
	XMFLOAT3 pos;	//xyz���W
	XMFLOAT3 normal;//�@���x�N�g��
	XMFLOAT2 uv;	//uv���W
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
	std::vector<Vertex> vertices2;
	std::vector<uint16_t> indices;
	std::vector<uint16_t> indices2;

	ID3D12PipelineState* pipelineState[3];
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView2{};
	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};
	//���\�[�X�ݒ�
	ID3D12Resource* constBuffMaterial = nullptr;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView2{};

	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// �F (RGBA)
	};


	//ID3D12Resource* constBuffTransform0 = nullptr;
	//ConstBufferDataTransform* constMapTransform0 = nullptr;

	//ID3D12Resource* constBuffTransform1 = nullptr;
	//ConstBufferDataTransform* constMapTransform1 = nullptr;

	//�F
	ConstBufferDataMaterial* constMapMaterial;

	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//�J�����֌W
	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;

	XMMATRIX matWorld;
	XMMATRIX matWorld1;
	XMMATRIX matView;
	XMMATRIX matProjection;

	//�X�P�[�����O0
	XMMATRIX matScale;
	//��]0
	XMMATRIX matRot;
	//���s�ړ�0
	XMMATRIX matTrans;

	//�X�P�[�����O1
	XMMATRIX matScale1;
	//��]1
	XMMATRIX matRot1;
	//���s�ړ�1
	XMMATRIX matTrans1;

	//�X�P�[�����O���W0
	XMFLOAT3 scale;
	//��]�p0
	XMFLOAT3 rotation;
	//���W0
	XMFLOAT3 position;

	//�X�P�[�����O���W1
	XMFLOAT3 scale1;
	//��]�p1
	XMFLOAT3 rotation1;
	//���W1
	XMFLOAT3 position1;

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC depthResourceDesc{};
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	D3D12_CLEAR_VALUE depthClearValue{};

	//���\�[�X����
	ID3D12Resource* depthBuff = nullptr;

	//�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ID3D12DescriptorHeap* dsvHeap = nullptr;

	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//�z��
	static const size_t kObjectCount = 5;

	Object3d object3ds[kObjectCount];
};

