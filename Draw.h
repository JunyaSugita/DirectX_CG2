#pragma once
#include "IniDX.h"
#include <DirectXMath.h>
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include "Object3d.h"

struct Vertex {
	XMFLOAT3 pos;	//xyz座標
	XMFLOAT3 normal;//法線ベクトル
	XMFLOAT2 uv;	//uv座標
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
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView2{};
	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[3] = {};
	//リソース設定
	ID3D12Resource* constBuffMaterial = nullptr;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView2{};

	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;		// 色 (RGBA)
	};


	//ID3D12Resource* constBuffTransform0 = nullptr;
	//ConstBufferDataTransform* constMapTransform0 = nullptr;

	//ID3D12Resource* constBuffTransform1 = nullptr;
	//ConstBufferDataTransform* constMapTransform1 = nullptr;

	//色
	ConstBufferDataMaterial* constMapMaterial;

	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//カメラ関係
	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;

	XMMATRIX matWorld;
	XMMATRIX matWorld1;
	XMMATRIX matView;
	XMMATRIX matProjection;

	//スケーリング0
	XMMATRIX matScale;
	//回転0
	XMMATRIX matRot;
	//平行移動0
	XMMATRIX matTrans;

	//スケーリング1
	XMMATRIX matScale1;
	//回転1
	XMMATRIX matRot1;
	//平行移動1
	XMMATRIX matTrans1;

	//スケーリング座標0
	XMFLOAT3 scale;
	//回転角0
	XMFLOAT3 rotation;
	//座標0
	XMFLOAT3 position;

	//スケーリング座標1
	XMFLOAT3 scale1;
	//回転角1
	XMFLOAT3 rotation1;
	//座標1
	XMFLOAT3 position1;

	//リソース設定
	D3D12_RESOURCE_DESC depthResourceDesc{};
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	D3D12_CLEAR_VALUE depthClearValue{};

	//リソース生成
	ID3D12Resource* depthBuff = nullptr;

	//深度ビュー用デスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ID3D12DescriptorHeap* dsvHeap = nullptr;

	//深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//配列
	static const size_t kObjectCount = 5;

	Object3d object3ds[kObjectCount];
};

