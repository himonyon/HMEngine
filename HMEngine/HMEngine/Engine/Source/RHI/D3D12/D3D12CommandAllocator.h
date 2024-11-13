// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12CommandAllocator;

class D3D12CommandAllocator
{
public:
	bool CreateCommandAllocator(ComPtr<ID3D12Device> pDevice);

	ComPtr<ID3D12CommandAllocator> GetCommandAllocator();

private:
	ComPtr<ID3D12CommandAllocator> m_pCommandAllocator;
};