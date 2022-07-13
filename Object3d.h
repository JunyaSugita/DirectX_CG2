#pragma once
#include "WorldTransform.h"

class Object3d {
public:
	//定数バッファ(行列用)
	ID3D12Resource* constBuffTransform;

	//定数バッファマップ(行列用)
	ConstBufferDataTransform* constMapTransform;

	////アフィン変換情報
	//XMFLOAT3 scale = { 1,1,1 };
	//XMFLOAT3 rotation = { 0,0,0 };
	//XMFLOAT3 position = { 0,0,0 };

	////ワールド変換行列
	//Matrix4 matWorld;

	////親のオブジェクトへのポインタ
	//Object3d* parent = nullptr;

	WorldTransform worldTransform;

public:
	void InitializeObject3d(ID3D12Device* device);

	void UpdateObject3d(XMMATRIX& matView, XMMATRIX& matProjection);
	
};

