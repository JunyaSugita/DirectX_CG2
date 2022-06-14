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
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[3] = {};
	//リソース設定
	ID3D12Resource* constBuffMaterial = nullptr;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// 色 (RGBA)
	};
	//定数バッファ用データ構造体(3D変換行列)
	struct ConstBufferDataTransform {
		XMMATRIX mat;		// 3D変換行列
	};

	ID3D12Resource* constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//色
	ConstBufferDataMaterial* constMapMaterial;

	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//カメラ関係
	XMMATRIX matview;
	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;

	XMMATRIX matProjection;
};

