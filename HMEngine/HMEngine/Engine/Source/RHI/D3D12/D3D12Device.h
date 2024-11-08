// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct IDXGIAdapter;

class D3D12Device
{
public:
	bool CreateD3D12Device(ComPtr<IDXGIAdapter> adapter);

	ComPtr<ID3D12Device> GetD3D12Device();
private:
	ComPtr<ID3D12Device> m_pDevice;
};