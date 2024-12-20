// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include "../../include/common.h"

class DXGIAdapter;
class DXGISwapChain;
class D3D12Device;
class D3D12PipelineStateObject;
class D3D12CommandList;
class D3D12CommandQueue;
class D3D12DescriptorHeap;
class D3D12RenderTargetView;
class D3D12CommandAllocator;
class D3D12RootSignature;

class D3D12RHI
{
public:
	D3D12RHI();
	~D3D12RHI();

	void Initialize();
	void Update();
	void Render();
	void Destroy();

private:
	void LoadPipeline();
	void LoadAssets();


	u_ptr<DXGIAdapter> m_pDXGIAdapter;
	u_ptr<DXGISwapChain> m_pDXGISwapChain;
	u_ptr<D3D12Device> m_pD3D12Device;
	u_ptr<D3D12PipelineStateObject> m_pD3D12PipelineStateObject;
	u_ptr<D3D12CommandList> m_pD3D12CommandList;
	u_ptr<D3D12CommandQueue> m_pD3D12CommandQueue;
	u_ptr<D3D12CommandAllocator> m_pD3D12CommandAllocator;
	u_ptr<D3D12DescriptorHeap> m_pD3D12DescriptorHeap;
	u_ptr<D3D12RenderTargetView> m_pD3D12RenderTargetView;
	u_ptr<D3D12RootSignature> m_pD3D12RootSignature;
};