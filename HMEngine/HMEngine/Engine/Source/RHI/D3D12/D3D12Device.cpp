// Copyright (c) 2024 YukiHino. All rights reserved.

#include <iostream>
#include "include/d3x12.h"
#include "D3D12Adapter.h"
#include "D3D12Device.h"

bool D3D12Device::CreateDevice(ComPtr<IDXGIAdapter> adapter)
{
	//Create Device
	
	D3D_FEATURE_LEVEL featureLevels[5] = 
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	for (int index = 0; index < std::size(featureLevels); index++)
	{
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevels[index], IID_PPV_ARGS(&m_device))))
		{
			return true;
		}
	}

	return false;
}