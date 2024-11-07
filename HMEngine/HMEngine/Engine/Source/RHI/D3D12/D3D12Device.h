// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct IDXGIAdapter;

class D3D12Device
{
public:
	bool CreateDevice(ComPtr<IDXGIAdapter> adapter);
private:
	ComPtr<ID3D12Device> m_device;
};