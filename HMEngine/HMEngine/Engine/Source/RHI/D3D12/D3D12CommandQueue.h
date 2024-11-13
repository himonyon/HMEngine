// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct ID3D12CommandQueue;

class D3D12CommandQueue
{
public:
	bool CreateCommandQueue(ComPtr<ID3D12Device> pDevice);

public:
	ComPtr<ID3D12CommandQueue> GetCommandQueue();

private:
	ComPtr<ID3D12CommandQueue> m_pCommandQueue;
};
