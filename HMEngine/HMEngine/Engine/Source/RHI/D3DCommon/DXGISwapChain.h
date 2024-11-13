// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct IDXGIFactory2;
struct IDXGISwapChain1;
struct ID3D12CommandQueue;

class DXGISwapChain
{
public:
	bool CreateSwapChian_ForD3D12(ComPtr<IDXGIFactory2> pFactory, ComPtr<ID3D12CommandQueue> pDevice);

	ComPtr<IDXGISwapChain1> GetSwapChain();
public:
	static const UINT FrameCount = 2; 

private:
	ComPtr<IDXGISwapChain1> m_pSwapChain;
};