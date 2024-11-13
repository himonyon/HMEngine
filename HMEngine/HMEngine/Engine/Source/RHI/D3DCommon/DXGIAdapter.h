// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct IDXGIFactory6;
struct IDXGIAdapter4;

class DXGIAdapter
{
public:
	bool CreateFactory();
	bool CreateAdapter();

public:
	ComPtr<IDXGIAdapter4> GetAdapter();
	ComPtr<IDXGIFactory6> GetFactory();

private:
	ComPtr<IDXGIFactory6> m_pFactory6;	

	ComPtr<IDXGIAdapter4> m_pAdapter4;
};