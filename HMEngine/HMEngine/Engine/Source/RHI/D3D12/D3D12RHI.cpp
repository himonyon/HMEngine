// Copyright (c) 2024 YukiHino. All rights reserved.

#include "include/d3x12.h"
#include "../D3DCommon/DXGIAdapter.h"
#include "../D3DCommon/DXGISwapChain.h"
#include "D3D12CommandQueue.h"
#include "D3D12Device.h"
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
	
	//Create adapter
	m_pDXGIAdapter = std::make_unique<DXGIAdapter>();
	ThrowIfFailed(m_pDXGIAdapter->CreateDXGIFactory(), "DXGIFactory did not find.");
	ThrowIfFailed(m_pDXGIAdapter->CreateDXGIAdapter(), "DXGIAdapter did not find.");

	//Create device
	m_pD3D12Device = std::make_unique<D3D12Device>();
	ThrowIfFailed(m_pD3D12Device->CreateD3D12Device(m_pDXGIAdapter->GetDXGIAdapter()), "D3D12Device did not find.");

	//Create command queue
	m_pD3D12CommandQueue = std::make_unique<D3D12CommandQueue>();
	ThrowIfFailed(m_pD3D12CommandQueue->CreateD3D12CommandQueue(m_pD3D12Device->GetD3D12Device()), "D3D12CommandQueue did not find.");

	//Create wwap chain
	m_pDXGISwapChain = std::make_unique<DXGISwapChain>();
	ThrowIfFailed(m_pDXGISwapChain->CreateSwapChian_ForD3D12(m_pDXGIAdapter->GetDXGIFactory(), m_pD3D12CommandQueue->GetCommandQueue()), "");

	//Create heap description

}