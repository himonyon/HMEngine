// Copyright (c) 2024 YukiHino. All rights reserved.

#include <dxgi1_2.h>
#include <d3d12.h>

#include "../../Core/HMEngine.h"
#include "DXGISwapChain.h"

bool DXGISwapChain::CreateDXGISwapChian_ForD3D12(ComPtr<IDXGIFactory2> pFactory, ComPtr<ID3D12CommandQueue> pCommandQueue)
{
	DXGI_SWAP_CHAIN_DESC1 desc;
	//SwapChain Buffer Setting
	desc.Width = 0;
	desc.Height = 0;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Stereo = FALSE;
	//MSAA Setting
	//TODO: Reconfigration when verifying MSAA
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//Usage
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//else
	desc.BufferCount = FrameCount;
	desc.Scaling = DXGI_SCALING_STRETCH;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	//FullScreen setting desc
	//DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc;
	ComPtr<IDXGISwapChain1> tmpSwapChain;
	if (SUCCEEDED(pFactory->CreateSwapChainForHwnd(pCommandQueue.Get(), HMEngine::GetWnd(), &desc, NULL, NULL, &m_pDXGISwapChain)))
	{
		return false;
	}

	return true;
}