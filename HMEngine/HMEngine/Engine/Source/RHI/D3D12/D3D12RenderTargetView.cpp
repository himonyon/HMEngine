// Copyright (c) 2024 YukiHino. All rights reserved.

#include <dxgi1_2.h>
#include <d3d12.h>
#include "../D3DCommon/DXGISwapChain.h"
#include "D3D12RenderTargetView.h"

bool D3D12RenderTargetView::CreateD3D12RenderTargetView(ComPtr<ID3D12Device> pDevice, ComPtr<IDXGISwapChain1> pSwapChain, int index, D3D12_CPU_DESCRIPTOR_HANDLE& handle)
{
	if (index < DXGISwapChain::FrameCount)
	{
		pSwapChain->GetBuffer(index, IID_PPV_ARGS(&m_pRenderTargetViews[index]));
		pDevice->CreateRenderTargetView(m_pRenderTargetViews[index].Get(), nullptr, handle);
		if (m_pRenderTargetViews[index] != nullptr)
		{
			return true;
		}
	}

	return false;
}

ComPtr<ID3D12Resource> D3D12RenderTargetView::GetRenderTargetView(int index)
{
	if (index < DXGISwapChain::FrameCount)
	{
		return m_pRenderTargetViews[index];
	}
	return NULL;
}