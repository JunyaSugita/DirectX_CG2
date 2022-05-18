#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <vector>
#include <string>
#include "vcruntime.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

class IniDX{
public:
	IniDX();
	~IniDX();
public:
	void Ini(HWND hwnd);
public:
	HRESULT result;
	ID3D12Device* device;
	IDXGIFactory7* dxgiFactory;
	IDXGISwapChain4* swapChain;
	ID3D12CommandAllocator* commandAllocator;
	ID3D12GraphicsCommandList* commandList;
	ID3D12CommandQueue* commandQueue;
	ID3D12DescriptorHeap* rtvHeap;
	std::vector<ID3D12Resource*> backBuffers;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	ID3D12Fence* fence;
	UINT64 fenceVal;
	// ‘Î‰žƒŒƒxƒ‹‚Ì”z—ñ
	D3D_FEATURE_LEVEL levels[4];
};

