// Copyright (c) 2024 YukiHino. All rights reserved.

#include <d3d12.h>
#include "D3D12CommandList.h"

bool D3D12CommandList::CreateCommandList(ComPtr<ID3D12Device> pDevice, ComPtr<ID3D12CommandAllocator> pCommandAllocator, ComPtr<ID3D12PipelineState> pPipelineState)
{
	if (FAILED(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator.Get(), pPipelineState.Get(), IID_PPV_ARGS(&m_pCommandList))))
	{
		return false;
	}
	return true;
}

ComPtr<ID3D12GraphicsCommandList> D3D12CommandList::GetCommandList()
{
	return m_pCommandList;
}