// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

class DXGISwapChain;
struct ID3D12Device;
struct ID3D12Resource;
struct D3D12_CPU_DESCRIPTOR_HANDLE;

class D3D12RenderTargetView
{
public:
	bool CreateD3D12RenderTargetView(ComPtr<ID3D12Device> pDevice, int index, D3D12_CPU_DESCRIPTOR_HANDLE& handle);

	ComPtr<ID3D12Resource> GetD3D12RenderTargetView(int index);
private:
	ComPtr<ID3D12Resource> m_pD3D12RenderTargetViews[DXGISwapChain::FrameCount];
};
