// Copyright (c) 2024 YukiHino. All rights reserved.

#include <d3d12.h>
#include "D3D12CommandQueue.h"

bool D3D12CommandQueue::CreateCommandQueue(ComPtr<ID3D12Device> pDevice)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	if (SUCCEEDED(pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_pCommandQueue))))
	{
		return true;
	}
	return false;
}

ComPtr<ID3D12CommandQueue> D3D12CommandQueue::GetCommandQueue()
{
	return m_pCommandQueue;
}