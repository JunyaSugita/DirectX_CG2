#pragma once
#include "WorldTransform.h"

class Object3d {
public:
	//�萔�o�b�t�@(�s��p)
	ID3D12Resource* constBuffTransform;

	//�萔�o�b�t�@�}�b�v(�s��p)
	ConstBufferDataTransform* constMapTransform;

	////�A�t�B���ϊ����
	//XMFLOAT3 scale = { 1,1,1 };
	//XMFLOAT3 
	// 
	// ation = { 0,0,0 };
	//XMFLOAT3 position = { 0,0,0 };

	////���[���h�ϊ��s��
	//Matrix4 matWorld;

	////�e�̃I�u�W�F�N�g�ւ̃|�C���^
	//Object3d* parent = nullptr;

	WorldTransform worldTransform;

public:
	void InitializeObject3d(ID3D12Device* device);

	void UpdateObject3d();

};

void Draw3dObject(Object3d* object, ID3D12GraphicsCommandList* commandList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices);
