// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include "../../include/common.h"

class DXGIAdapter;
class DXGISwapChain;
class D3D12Device;
class D3D12CommandQueue;
class D3D12DescriptorHeap;

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
	u_ptr<DXGIAdapter> m_pDXGIAdapter;
	u_ptr<DXGISwapChain> m_pDXGISwapChain;
	u_ptr<D3D12Device> m_pD3D12Device;
	u_ptr<D3D12CommandQueue> m_pD3D12CommandQueue;
	u_ptr<D3D12DescriptorHeap> m_pD3D12DescriptorHeap;
};