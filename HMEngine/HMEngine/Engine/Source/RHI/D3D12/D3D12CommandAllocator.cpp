// Copyright (c) 2024 YukiHino. All rights reserved.

#include <d3d12.h>
#include "D3D12CommandAllocator.h"

bool D3D12CommandAllocator::CreateCommandAllocator(ComPtr<ID3D12Device> pDevice)
{
	HRESULT hr;
	if (SUCCEEDED(hr = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pCommandAllocator))))
	{
		return true;
	}
	return false;
}

ComPtr<ID3D12CommandAllocator> D3D12CommandAllocator::GetCommandAllocator()
{
	return m_pCommandAllocator;
}
