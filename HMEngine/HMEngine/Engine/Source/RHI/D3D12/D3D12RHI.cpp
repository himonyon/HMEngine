// Copyright (c) 2024 YukiHino. All rights reserved.

#include "include/d3x12.h"
#include "D3D12Util.h"

#include "D3D12RHI.h"

void D3D12RHI::Initialize()
{
#if HM_DEBUG
	//TODO: Debug layer setting
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	int index = 0;

	//CreateDXGI Factory
	UINT dxgiCreateFactoryFlag = 0;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ThrowIfFailed(CreateDXGIFactory2(dxgiCreateFactoryFlag, IID_PPV_ARGS(&dxgiFactory)), "DXGIFactory Create Faild.");

	//Device initialize
	ComPtr<IDXGIAdapter4> adapter;
	D3D_FEATURE_LEVEL featureLevels[5] = 
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	//Get best hardware adapter
	for (index = 0; SUCCEEDED(dxgiFactory->EnumAdapterByGpuPreference(index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter))); index++)
	{
		for (int level = 0; level < 5; level++)
		{
			//Create Device
			if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevels[level], IID_PPV_ARGS(&m_device))))
			{
				break;
			}
		}
	}

	//if hardware adapter did not find, get WARP adapter
	if (!adapter || !m_device)
	{
		ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)), "Adapter did not find.");
		for (int level = 0; level < 5; level++)
		{
			//Create Device
			if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevels[level], IID_PPV_ARGS(&m_device))))
			{
				break;
			}
		}
		if (!m_device)
		{
			ThrowIfFailed(FALSE, "Device did not find.");
		}
	}
}