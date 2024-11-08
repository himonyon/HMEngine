// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct IDXGIFactory6;
struct IDXGIAdapter4;

class D3D12Adapter
{
public:
	bool CreateDXGIFactory();
	bool CreateDXGIAdapter();

public:
	ComPtr<IDXGIAdapter4> GetDXGIAdapter();

private:
	ComPtr<IDXGIFactory6> m_pFactory6;	

	ComPtr<IDXGIAdapter4> m_pAdapter4;
};