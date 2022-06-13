#include "Graphics.h"

Graphics::Graphics() {
}

Graphics::~Graphics() {
}

void Graphics::Process(IniDX* iniDX, Draw* draw) {
	// バックバッファの番号を取得(2つなので0番か1番)
	UINT bbIndex = iniDX->swapChain->GetCurrentBackBufferIndex();
	// 1.リソースバリアで書き込み可能に変更
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = iniDX->backBuffers[bbIndex]; // バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // 表示状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態へ
	iniDX->commandList->ResourceBarrier(1, &barrierDesc);
	// 2.描画先の変更
	// レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = iniDX->rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * iniDX->device->GetDescriptorHandleIncrementSize(iniDX->rtvHeapDesc.Type);
	iniDX->commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	// 3.画面クリア R G B A
	FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f }; // 青っぽい色
	iniDX->commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	// 4.描画コマンド
	// ビューポート設定コマンド
	D3D12_VIEWPORT viewport{};
	viewport.Width = WIN_WIDTH;
	viewport.Height = WIN_HEIGHT;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// ビューポート設定コマンドを、コマンドリストに積む
	iniDX->commandList->RSSetViewports(1, &viewport);

	// シザー矩形
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // 切り抜き座標左
	scissorRect.right = scissorRect.left + WIN_WIDTH; // 切り抜き座標右
	scissorRect.top = 0; // 切り抜き座標上
	scissorRect.bottom = scissorRect.top + WIN_HEIGHT; // 切り抜き座標下
	// シザー矩形設定コマンドを、コマンドリストに積む
	iniDX->commandList->RSSetScissorRects(1, &scissorRect);

	// パイプラインステートとルートシグネチャの設定コマンド
	iniDX->commandList->SetPipelineState(draw->pipelineState);
	iniDX->commandList->SetGraphicsRootSignature(draw->rootSignature);

	// プリミティブ形状の設定コマンド///////////////////////////////////////////////////////
	iniDX->commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);// 
	//////////////////////////////////////////////////////////////////////////////////
	// 頂点バッファビューの設定コマンド
	iniDX->commandList->IASetVertexBuffers(0, 1, &draw->vbView);

	//定数バッファビュー(CBV)の設定コマンド
	iniDX->commandList->SetGraphicsRootConstantBufferView(0, draw->constBuffMaterial->GetGPUVirtualAddress());
	//SRVヒープの設定コマンド
	iniDX->commandList->SetDescriptorHeaps(1, &draw->srvHeap);
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = draw->srvHeap->GetGPUDescriptorHandleForHeapStart();
	//SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	iniDX->commandList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//定数バッファビュー(CBV)の設定コマンド
	iniDX->commandList->SetGraphicsRootConstantBufferView(2, draw->constBuffTransform->GetGPUVirtualAddress());

	//インデックスバッファビューの設定コマンド
	iniDX->commandList->IASetIndexBuffer(&draw->ibView);

	// 描画コマンド
	//iniDX->commandList->DrawInstanced(draw->vertices.size(), 1, 0, 0);
	iniDX->commandList->DrawIndexedInstanced(draw->indices.size(), 1, 0, 0, 0); // 全ての頂点を使って描画

	// 5.リソースバリアを戻す
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // 表示状態へ
	iniDX->commandList->ResourceBarrier(1, &barrierDesc);

	// 命令のクローズ
	iniDX->result = iniDX->commandList->Close();
	assert(SUCCEEDED(iniDX->result));
	// コマンドリストの実行
	ID3D12CommandList* commandLists[] = { iniDX->commandList };
	iniDX->commandQueue->ExecuteCommandLists(1, commandLists);
	// 画面に表示するバッファをフリップ(裏表の入替え)
	iniDX->result = iniDX->swapChain->Present(1, 0);
	assert(SUCCEEDED(iniDX->result));

	// コマンドの実行完了を待つ
	iniDX->commandQueue->Signal(iniDX->fence, ++iniDX->fenceVal);
	if (iniDX->fence->GetCompletedValue() != iniDX->fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		iniDX->fence->SetEventOnCompletion(iniDX->fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	// キューをクリア
	iniDX->result = iniDX->commandAllocator->Reset();
	assert(SUCCEEDED(iniDX->result));
	// 再びコマンドリストを貯める準備
	iniDX->result = iniDX->commandList->Reset(iniDX->commandAllocator, nullptr);
	assert(SUCCEEDED(iniDX->result));
}
