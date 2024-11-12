// Copyright (c) 2024 YukiHino. All rights reserved.

#include "include/d3x12.h"
#include "../D3DCommon/DXGISwapChain.h"
#include "D3D12RenderTargetView.h"

bool D3D12RenderTargetView::CreateD3D12RenderTargetView(ComPtr<ID3D12Device> pDevice, int index, D3D12_CPU_DESCRIPTOR_HANDLE& handle)
{
	if (index < DXGISwapChain::FrameCount)
	{
		pDevice->CreateRenderTargetView(m_pD3D12RenderTargetViews[index].Get(), nullptr, handle);
	}

	return false;
}

ComPtr<ID3D12Resource> D3D12RenderTargetView::GetD3D12RenderTargetView(int index)
{
	if (index < DXGISwapChain::FrameCount)
	{
		return m_pD3D12RenderTargetViews[index];
	}
	return NULL;
}