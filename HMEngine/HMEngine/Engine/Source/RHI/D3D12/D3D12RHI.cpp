// Copyright (c) 2024 YukiHino. All rights reserved.

#include "include/d3x12.h"
#include "D3D12Device.h"
#include "D3D12Adapter.h"
#include "D3D12Util.h"
#include "D3D12RHI.h"

//TODO: Forward declaration in class with smart pointers must implement special member functions??
D3D12RHI::D3D12RHI() = default;
D3D12RHI::~D3D12RHI() = default;

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
	
	//Create Adapter
	m_d3d12Adapter = std::make_unique<D3D12Adapter>();
	ThrowIfFailed(m_d3d12Adapter->CreateFactory(), "DXGIFactory did not find.");
	ThrowIfFailed(m_d3d12Adapter->CreateAdapter(), "DXGIAdapter did not find.");

	//Create Device
	m_d3d12Device = std::make_unique<D3D12Device>();
	ThrowIfFailed(m_d3d12Device->CreateDevice(m_d3d12Adapter->GetAdapter()), "D3D12Device did not find.");
}