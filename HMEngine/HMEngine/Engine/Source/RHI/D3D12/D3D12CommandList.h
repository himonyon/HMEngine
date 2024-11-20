// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct ID3D12GraphicsCommandList;

class D3D12CommandList
{
public:
	bool CreateCommandList(ComPtr<ID3D12Device> pDevice, ComPtr<ID3D12CommandAllocator> pCommandAllocator, ComPtr<ID3D12PipelineState> pPipelineState);

	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
private:
	ComPtr<ID3D12GraphicsCommandList> m_pCommandList;
};