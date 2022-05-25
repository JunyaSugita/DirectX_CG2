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
	XMFLOAT3 vertices[3];

	ID3D12PipelineState* pipelineState;
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParam = {};
	//リソース設定
	ID3D12Resource* constBuffMaterial = nullptr;

	//
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// 色 (RGBA)
	};
	//色
	ConstBufferDataMaterial* constMapMaterial;
};

