// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct ID3D12RootSignature;

class D3D12RootSignature
{
public:
	bool CreateRootSignature(ComPtr<ID3D12Device> pDevice);

	ComPtr<ID3D12RootSignature> GetRootSignature();

private:
	ComPtr<ID3D12RootSignature> m_pRootSignature;
};
