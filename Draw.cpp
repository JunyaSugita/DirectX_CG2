#include "Draw.h"
#include <DirectXTex.h>
#include "WinSize.h"


Draw::Draw() {
	//scale = { 1.0f,1.0f,1.0f };
	//rotation = { 0.0f,0.0f,0.0f };
	//position = { 0.0f,0.0f,0.0f };

	//scale1 = { 1.0f,1.0f,1.0f };
	//rotation1 = { 0.0f,XM_PI/4.0f,0.0f };
	//position1 = { -20.0f,0.0f,0.0f };
}

Draw::~Draw() {}

void Draw::Ini(IniDX* iniDX) {
	//頂点データ
	vertices = std::vector<Vertex>({
		//前
		{ { -5.0f,-5.0f,-5.0f},{},{0.0f,1.0f} },		//左下
		{ { -5.0f, 5.0f,-5.0f},{},{0.0f,0.0f} },		//左上
		{ {  5.0f,-5.0f,-5.0f},{},{1.0f,1.0f} },		//右下
		{ {  5.0f, 5.0f,-5.0f},{},{1.0f,0.0f} },		//右上

		//後
		{ { -5.0f,-5.0f, 5.0f},{},{0.0f,1.0f} },		//左下
		{ { -5.0f, 5.0f, 5.0f},{},{0.0f,0.0f} },		//左上
		{ {  5.0f,-5.0f, 5.0f},{},{1.0f,1.0f} },		//右下
		{ {  5.0f, 5.0f, 5.0f},{},{1.0f,0.0f} },		//右上

		//左
		{ { -5.0f,-5.0f,-5.0f},{},{0.0f,1.0f} },		//左下
		{ { -5.0f,-5.0f, 5.0f},{},{0.0f,0.0f} },		//左上
		{ { -5.0f, 5.0f,-5.0f},{},{1.0f,1.0f} },		//右下
		{ { -5.0f, 5.0f, 5.0f},{},{1.0f,0.0f} },		//右上

		//右
		{ {  5.0f,-5.0f,-5.0f},{},{0.0f,1.0f} },		//左下
		{ {  5.0f,-5.0f, 5.0f},{},{0.0f,0.0f} },		//左上
		{ {  5.0f, 5.0f,-5.0f},{},{1.0f,1.0f} },		//右下
		{ {  5.0f, 5.0f, 5.0f},{},{1.0f,0.0f} },		//右上

		//下
		{ { -5.0f,-5.0f,-5.0f},{},{0.0f,1.0f} },		//左下
		{ { -5.0f,-5.0f, 5.0f},{},{0.0f,0.0f} },		//左上
		{ {  5.0f,-5.0f,-5.0f},{},{1.0f,1.0f} },		//右下
		{ {  5.0f,-5.0f, 5.0f},{},{1.0f,0.0f} },		//右上

		//上
		{ { -5.0f, 5.0f,-5.0f},{},{0.0f,1.0f} },		//左下
		{ { -5.0f, 5.0f, 5.0f},{},{0.0f,0.0f} },		//左上
		{ {  5.0f, 5.0f,-5.0f},{},{1.0f,1.0f} },		//右下
		{ {  5.0f, 5.0f, 5.0f},{},{1.0f,0.0f} },		//右上
		});

	
	indices = std::vector<uint16_t>({
		//前
		0,1,2,
		});

	//ビュー変換行列
	eye = { 0, 0, -100 };
	target = { 0, 0, 0 };
	up = { 0, 1, 0 };

	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	/*matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation.z);
	matRot *= XMMatrixRotationX(rotation.x);
	matRot *= XMMatrixRotationY(rotation.y);
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	matScale1 = XMMatrixScaling(scale1.x, scale1.y, scale1.z);
	matRot1 = XMMatrixIdentity();
	matRot1 *= XMMatrixRotationZ(rotation1.z);
	matRot1 *= XMMatrixRotationX(rotation1.x);
	matRot1 *= XMMatrixRotationY(rotation1.y);
	matTrans1 = XMMatrixTranslation(position1.x,position1.y,position1.z);

	matWorld.r[0] = { 1,0,0,0 };
	matWorld.r[1] = { 0,1,0,0 };
	matWorld.r[2] = { 0,0,1,0 };
	matWorld.r[3] = { 0,0,0,1 };

	matWorld1.r[0] = { 1,0,0,0 };
	matWorld1.r[1] = { 0,1,0,0 };
	matWorld1.r[2] = { 0,0,1,0 };
	matWorld1.r[3] = { 0,0,0,1 };

	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;

	matWorld1 *= matScale1;
	matWorld1 *= matRot1;
	matWorld1 *= matTrans1;*/

	for (size_t i = 0; i < _countof(object3ds); i++) {
		object3ds[i].UpdateObject3d();
	}


	// 頂点データ全体のサイズ = 頂点データ1つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * vertices.size());

	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};			//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;		//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;						//頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//頂点バッファの生成
	ID3D12Resource* vertBuff = nullptr;
	iniDX->result = iniDX->device->CreateCommittedResource(
		&heapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(iniDX->result));

	//インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * indices.size());

	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//インデックスバッファの生成
	ID3D12Resource* indexBuff = nullptr;
	iniDX->result = iniDX->device->CreateCommittedResource(
		&heapProp,	//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	//インデックスバッファをマッピング
	uint16_t* indexMap = nullptr;
	iniDX->result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//全インデックスに対して
	for (int i = 0; i < indices.size(); i++) {
		indexMap[i] = indices[i];
	}
	//マッピング解除
	indexBuff->Unmap(0, nullptr);

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//三角形1つごとに計算していく
	for (int i = 0; i < indices.size() / 3; i++) {
		//三角形のインデックスを取り出して一時的な変数を入れる
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		//三角形を編成する頂点座標をベクトルに代入
		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
		//p0->p1ベクトル、p0->p2ベクトルを計算(ベクトルを減算)
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//外積は両方から垂直なベクトル
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//正規化(長さを1にする)
		normal = XMVector3Normalize(normal);
		//求めた法線を頂点データに代入
		XMStoreFloat3(&vertices[index0].normal, normal);
		XMStoreFloat3(&vertices[index1].normal, normal);
		XMStoreFloat3(&vertices[index2].normal, normal);
	}

	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	Vertex* vertMap = nullptr;
	iniDX->result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(iniDX->result));
	// 全頂点に対して
	for (int i = 0; i < vertices.size(); i++) {
		vertMap[i] = vertices[i]; // 座標をコピー
	}
	// 繋がりを解除
	vertBuff->Unmap(0, nullptr);

	// GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// 頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	// 頂点1つ分のデータサイズ
	vbView.StrideInBytes = sizeof(vertices[0]);

	ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
	ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
	ID3DBlob* errorBlob = nullptr; // エラーオブジェクト
	// 頂点シェーダの読み込みとコンパイル
	iniDX->result = D3DCompileFromFile(
		L"BasicVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	// エラーなら
	if (FAILED(iniDX->result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// ピクセルシェーダの読み込みとコンパイル
	iniDX->result = D3DCompileFromFile(
		L"BasicPS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);

	// エラーなら
	if (FAILED(iniDX->result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}, // (1行で書いたほうが見やすい)
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},		//法線ベクトル
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//デプスステンシルステートの設定
	pipelineDesc.DepthStencilState.DepthEnable = true;	//深度テストを行う
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//書き込み許可
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;	//小さければ合格
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;	//深度値フォーマット

	// シェーダーの設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面カリング
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// ブレンドステート
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask
	//	= D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	blenddesc.BlendEnable = true;					//ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	//加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		//ソースの100%使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	//デストの値を0%使う

	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;			//加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;		//ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;//1.0f-ソースのアルファ値

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	/////////////////////////////////
	//定数バッファ用データ構造体(マテリアル)
	/////////////////////////////////
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;	//256バイトアラインメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	constBuffMaterial = nullptr;
	//定数バッファの生成
	iniDX->result = iniDX->device->CreateCommittedResource(
		&cbHeapProp,		//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial)
	);
	assert(SUCCEEDED(iniDX->result));

	//定数バッファのマッピング
	constMapMaterial = nullptr;
	iniDX->result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	//マッピング
	assert(SUCCEEDED(iniDX->result));

	//値を書き込むと自動的に転送される
	constMapMaterial->color = XMFLOAT4(1, 1, 1, 1);	//RGBAで半透明の赤
	//////////////////
	//テクスチャの初期化
	//////////////////

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WICテクスチャのロード
	iniDX->result = LoadFromWICFile(
		L"Resources/texture.png",	//「Resources」フォルダの「texture.png」
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);

	ScratchImage mipChain{};
	//ミップマップ生成
	iniDX->result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(iniDX->result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = MakeSRGB(metadata.format);

	////横方向ピクセル数
	//const size_t textureWidth = 256;
	////縦方向ピクセル数
	//const size_t textureHeight = 256;
	////配列の要素数
	//const size_t imageDataCount = textureWidth * textureHeight;
	////画像イメージデータ配列
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];

	////全ピクセルの色を初期化
	//for (size_t i = 0; i < imageDataCount; i++) {
	//	if (i % 20 < 10) {
	//		imageData[i].x = 0.0f;	//R
	//		imageData[i].y = 1.0f;	//G
	//		imageData[i].z = 0.0f;	//B
	//		imageData[i].w = 1.0f;	//A
	//	}
	//	else {
	//		imageData[i].x = 0.0f;	//R
	//		imageData[i].y = 1.0f;	//G
	//		imageData[i].z = 0.0f;	//B
	//		imageData[i].w = 0.0f;	//A
	//	}
	//}

	//ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;
	textureResourceDesc.Height = (UINT)metadata.height;
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//テクスチャバッファの生成
	ID3D12Resource* texBuff = nullptr;
	iniDX->result = iniDX->device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff)
	);
	//全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		//ミップマップレベルを指定してイメージを取得
		const Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		iniDX->result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,
			img->pixels,
			(UINT)img->rowPitch,
			(UINT)img->slicePitch
		);
		assert(SUCCEEDED(iniDX->result));
	}

	//元データ解放
	//delete[] imageData;

	//SRVの最大個数
	const size_t kMaxSRVCount = 2056;


	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	//設定を元にSRV用デスクリプタヒープを生成
	iniDX->result = iniDX->device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(iniDX->result));

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	//シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;

	//ハンドルの指す位置にシェーダーリソースビュー作成
	iniDX->device->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);

	//デスクリプタレンジの設定
	descriptorRange.NumDescriptors = 1;
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	ConstBaffer(iniDX);
	//constMapTransform->mat = XMMatrixIdentity();
	//constMapTransform->mat.r[0].m128_f32[0] = 2.0f / WIN_WIDTH;
	//constMapTransform->mat.r[1].m128_f32[1] = -2.0f / WIN_HEIGHT;
	//constMapTransform->mat.r[3].m128_f32[0] = -1.0f;
	//constMapTransform->mat.r[3].m128_f32[1] = 1.0f;
	//constMapTransform0->mat = XMMatrixOrthographicOffCenterLH(
	//	0.0f, WIN_WIDTH,
	//	WIN_HEIGHT, 0.0f,
	//	0.0f, 1.0f
	//);
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),
		(float)WIN_WIDTH / WIN_HEIGHT,
		0.1f, 1000.0f
	);

	//定数バッファに転送
	//constMapTransform0->mat = matWorld * matView * matProjection;
	//constMapTransform1->mat = matWorld1 * matView * matProjection;


	//ルートパラメータ0番の設定
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;	//定数バッファビュー
	rootParams[0].Descriptor.ShaderRegister = 0;					//定数バッファ番号
	rootParams[0].Descriptor.RegisterSpace = 0;						//デフォルト値
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;	//全てのシェーダーから見える
	//テクスチャレジスタ0番
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;	//定数バッファビュー
	rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;			//定数バッファ番号
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;						//デフォルト値
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;				//全てのシェーダーから見える
	//定数バッファ1番
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParams[2].Descriptor.ShaderRegister = 1;
	rootParams[2].Descriptor.RegisterSpace = 0;
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					//横繰り返し(タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					//縦繰り返し(タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					//奥行き繰り返し(タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;	//ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;					//全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;									//ミップマップ最大値
	samplerDesc.MinLOD = 0.0f;												//ミップマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;			//ピクセルシェーダからのみ使用可能

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;					//ルートパラメータの先頭アドレス
	rootSignatureDesc.NumParameters = _countof(rootParams);		//ルートパラメータ数
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;
	// ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr;
	iniDX->result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);
	assert(SUCCEEDED(iniDX->result));
	iniDX->result = iniDX->device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(iniDX->result));
	rootSigBlob->Release();
	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature;

	// パイプランステートの生成
	pipelineState = nullptr;
	iniDX->result = iniDX->device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(iniDX->result));


}

void Draw::ConstBaffer(IniDX* iniDX) {
	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//配列内の全オブジェクトに対して////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < _countof(object3ds); i++) {
		//初期化
		object3ds[i].InitializeObject3d(iniDX->device);

		object3ds[0].worldTransform.scale = { 1.0f,1.0f,1.0f };
		object3ds[0].worldTransform.rotation = { 0.0f,0.0f,0.0f};
		object3ds[0].worldTransform.trans = { 0.0f,0.0f,0.0f };

		object3ds[1].worldTransform.scale = { 1.0f,2.0f,1.0f };
		object3ds[1].worldTransform.rotation = { 0.0f,0.0f,0.0f };
		object3ds[1].worldTransform.trans = { 50.0f,50.0f,10.0f };

		object3ds[2].worldTransform.scale = { 2.0f,1.0f,1.0f };
		object3ds[2].worldTransform.rotation = { 0.0f,0.0f,0.0f };
		object3ds[2].worldTransform.trans = { -50.0f,50.0f,20.0f };

		object3ds[3].worldTransform.scale = { 1.0f,3.0f,1.0f };
		object3ds[3].worldTransform.rotation = { 0.0f,0.0f,0.0f };
		object3ds[3].worldTransform.trans = { -50.0f,-50.0f,-20.0f };

		object3ds[4].worldTransform.scale = { 4.0f,4.0f,1.0f };
		object3ds[4].worldTransform.rotation = { 0.0f,0.0f,0.0f };
		object3ds[4].worldTransform.trans = { 50.0f,-50.0f,-10.0f };

		object3ds[5].worldTransform.scale = { 2.0f,3.0f,1.0f };
		object3ds[5].worldTransform.rotation = { XMConvertToRadians(180.0f),0.0f,0.0f };
		object3ds[5].worldTransform.trans = { 0.0f,50.0f,-30.0f };

		object3ds[6].worldTransform.scale = { 3.0f,2.0f,1.0f };
		object3ds[6].worldTransform.rotation = { XMConvertToRadians(180.0f),0.0f,0.0f };
		object3ds[6].worldTransform.trans = { 0.0f,-50.0f,10.0f };

		object3ds[7].worldTransform.scale = { 2.0f,2.0f,1.0f };
		object3ds[7].worldTransform.rotation = { XMConvertToRadians(180.0f),0.0f,0.0f };
		object3ds[7].worldTransform.trans = { -50.0f,0.0f,20.0f };

		object3ds[8].worldTransform.scale = { 4.0f,4.0f,1.0f };
		object3ds[8].worldTransform.rotation = { XMConvertToRadians(180.0f),0.0f,0.0f };
		object3ds[8].worldTransform.trans = { 50.0f,0.0f,-10.0f };

		//ここから↓は親子構造のサンプル
		//先頭以外なら
		//if (i > 0) {
			//1つ前のオブジェクトを親オブジェクトとする
			//object3ds[i].worldTransform.parent = &object3ds[i - 1].worldTransform;
			//親オブジェクトの9割の大きさ
			//object3ds[i].worldTransform.scale = { 0.9f,0.9f,0.9f };
			//親オブジェクトに対してZ軸まわりに30度回転
			//object3ds[i].worldTransform.rotation = { 0.0f,0.0f,/*XMConvertToRadians(30.0f) */ 0.0f};

			//親オブジェクトに対してZ方向-8.0ずらす
			//object3ds[i].worldTransform.trans = { 0.0f,0.0f,-8.0f };
		//}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//iniDX->result = iniDX->device->CreateCommittedResource(
	//	&cbHeapProp,
	//	D3D12_HEAP_FLAG_NONE,
	//	&cbResourceDesc,
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&constBuffTransform0)
	//);

	//定数バッファのマッピング
	//iniDX->result = constBuffTransform0->Map(0, nullptr, (void**)&constMapTransform0);
	//assert(SUCCEEDED(iniDX->result));

	//iniDX->result = iniDX->device->CreateCommittedResource(
	//	&cbHeapProp,
	//	D3D12_HEAP_FLAG_NONE,
	//	&cbResourceDesc,
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&constBuffTransform1)
	//);
	//定数バッファのマッピング
	//iniDX->result = constBuffTransform1->Map(0, nullptr, (void**)&constMapTransform1);
	//assert(SUCCEEDED(iniDX->result));
	

	//リソース設定
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = WIN_WIDTH;
	depthResourceDesc.Height = WIN_HEIGHT;
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	//深度値用ヒーププロパティ
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//深度値のクリア設定
	depthClearValue.DepthStencil.Depth = 1.0f;		//深度値1.0f(最大値)でクリア
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;	//深度値フォーマット

	//リソース生成
	iniDX->result = iniDX->device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,	//深度値書き込みに使用
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff)
	);

	//深度ビュー用デスクリプタヒープ作成
	dsvHeapDesc.NumDescriptors = 1;//深度ビューは1つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//デプスステンシルビュー
	iniDX->result = iniDX->device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	//深度ビュー作成
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	//深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	iniDX->device->CreateDepthStencilView(
		depthBuff,
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);
}