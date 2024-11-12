// Copyright (c) 2024 YukiHino. All rights reserved.

#include "include/d3x12.h"
#include "../D3DCommon/DXGISwapChain.h"
#include "D3D12Device.h"
#include "D3D12DescriptorHeap.h"

bool D3D12DescriptorHeap::CreateD3D12DescriptorHeap(ComPtr<ID3D12Device> pDevice)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.NumDescriptors = DXGISwapChain::FrameCount;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	desc.NodeMask = 0;

	if (SUCCEEDED(pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pD3D12DescriptorHeap))))
	{
		return true;
	}

	return false;
}

ComPtr<ID3D12DescriptorHeap> D3D12DescriptorHeap::GetDescriptorHeap()
{
	return m_pD3D12DescriptorHeap;
}