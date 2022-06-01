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

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	ID3D12PipelineState* pipelineState;
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[2] = {};
	//リソース設定
	ID3D12Resource* constBuffMaterial = nullptr;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// 色 (RGBA)
	};
	//色
	ConstBufferDataMaterial* constMapMaterial;

	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;
};

