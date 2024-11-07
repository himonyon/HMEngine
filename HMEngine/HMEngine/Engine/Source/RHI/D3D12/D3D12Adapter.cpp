// Copyright (c) 2024 YukiHino. All rights reserved.

#include <iostream>

#include "include/d3x12.h"
#include "D3D12Adapter.h"

bool D3D12Adapter::CreateFactory()
{
	//CreateDXGI Factory
	UINT dxgiCreateFactoryFlag = 0;
	if(SUCCEEDED(CreateDXGIFactory2(dxgiCreateFactoryFlag, IID_PPV_ARGS(&m_factory6))))
	{
		return true;
	}
	return false;
}

bool D3D12Adapter::CreateAdapter()
{
	//Create Adapter
	for (int index = 0; m_factory6->EnumAdapterByGpuPreference(index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&m_adapter4)) != DXGI_ERROR_NOT_FOUND; index++)
	{
		if (m_adapter4)
		{
			DXGI_ADAPTER_DESC desc{};
			m_adapter4->GetDesc(&desc);
			if (desc.VendorId == 0x1414 && desc.DeviceId == 0x8c)
			{
				//This is WARP Device
				continue;
			}
			else
			{
				return true;
			}
		}
	}

	//if hardware adapter did not find, get WARP adapter
	if(SUCCEEDED(m_factory6->EnumWarpAdapter(IID_PPV_ARGS(&m_adapter4))))
	{
		//TODO: Log (Select WARP Adapter)
		return true;
	}
	
	return false;
}

ComPtr<IDXGIAdapter4> D3D12Adapter::GetAdapter()
{
	return m_adapter4;
}