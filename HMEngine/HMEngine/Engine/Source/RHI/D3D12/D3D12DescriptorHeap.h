// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct ID3D12DescriptorHeap;

class D3D12DescriptorHeap
{
public:
	bool CreateD3D12DescriptorHeap(ComPtr<ID3D12Device> pDevice);

	ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap();
private:
	ComPtr<ID3D12DescriptorHeap> m_pD3D12DescriptorHeap;
};