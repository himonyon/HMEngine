// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct IDXGIFactory6;
struct IDXGIAdapter4;

class DXGIAdapter
{
public:
	bool CreateDXGIFactory();
	bool CreateDXGIAdapter();

public:
	ComPtr<IDXGIAdapter4> GetDXGIAdapter();
	ComPtr<IDXGIFactory6> GetDXGIFactory();

private:
	ComPtr<IDXGIFactory6> m_pFactory6;	

	ComPtr<IDXGIAdapter4> m_pAdapter4;
};