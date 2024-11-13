// Copyright (c) 2024 YukiHino. All rights reserved.

#include <iostream>
#include <d3d12.h>
#include <dxgi1_6.h>

#include "../D3DCommon/DXGIAdapter.h"
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
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevels[index], IID_PPV_ARGS(&m_pDevice))))
		{
			return true;
		}
	}

	return false;
}

ComPtr<ID3D12Device> D3D12Device::GetDevice()
{
	return m_pDevice;
}