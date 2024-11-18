// Copyright (c) 2024 YukiHino. All rights reserved.

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include "../D3DCommon/DXGIAdapter.h"
#include "../D3DCommon/DXGISwapChain.h"
#include "D3D12RootSignature.h"
#include "D3D12CommandList.h"
#include "D3D12CommandAllocator.h"
#include "D3D12RenderTargetView.h"
#include "D3D12DescriptorHeap.h"
#include "D3D12CommandQueue.h"
#include "D3D12Device.h"
#include "D3D12Util.h"
#include "D3D12RHI.h"

//TODO: Forward declaration in class with smart pointers must implement special member functions??
D3D12RHI::D3D12RHI() = default;
D3D12RHI::~D3D12RHI() = default;

void D3D12RHI::Initialize()
{
	LoadPipeline();
	LoadAssets();
}

void D3D12RHI::LoadPipeline()
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
	ThrowIfFailed(m_pDXGIAdapter->CreateFactory(), "DXGIFactory did not find.");
	ThrowIfFailed(m_pDXGIAdapter->CreateAdapter(), "DXGIAdapter did not find.");

	//Create device
	m_pD3D12Device = std::make_unique<D3D12Device>();
	ThrowIfFailed(m_pD3D12Device->CreateDevice(m_pDXGIAdapter->GetAdapter()), "Faild to create D3D12Device.");

	//Create command queue
	m_pD3D12CommandQueue = std::make_unique<D3D12CommandQueue>();
	ThrowIfFailed(m_pD3D12CommandQueue->CreateCommandQueue(m_pD3D12Device->GetDevice()), "Faild to create D3D12CommandQueue.");

	//Create swap chain
	m_pDXGISwapChain = std::make_unique<DXGISwapChain>();
	ThrowIfFailed(m_pDXGISwapChain->CreateSwapChian_ForD3D12(m_pDXGIAdapter->GetFactory(), m_pD3D12CommandQueue->GetCommandQueue()), "Faild to create DXGISwapChain");

	//Create descriptor heap
	m_pD3D12DescriptorHeap = std::make_unique<D3D12DescriptorHeap>();
	ThrowIfFailed(m_pD3D12DescriptorHeap->CreateDescriptorHeap(m_pD3D12Device->GetDevice()), "Faild to create D3D12DescriptorHeap.");

	//Create RTV
	UINT rtvDescriptorSize = m_pD3D12Device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_pD3D12DescriptorHeap->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	m_pD3D12RenderTargetView = std::make_unique<D3D12RenderTargetView>();
	for (int i = 0; i < DXGISwapChain::FrameCount; i++)
	{
		ThrowIfFailed(m_pD3D12RenderTargetView->CreateD3D12RenderTargetView(m_pD3D12Device->GetDevice(), m_pDXGISwapChain->GetSwapChain(), i, rtvHandle), "Faild to create D3D12RenderTargetView");
		rtvHandle.ptr += rtvDescriptorSize;
	}

	//Create command allocator
	m_pD3D12CommandAllocator = std::make_unique<D3D12CommandAllocator>();
	ThrowIfFailed(m_pD3D12CommandAllocator->CreateCommandAllocator(m_pD3D12Device->GetDevice()), "Faild to create D3D12CommandAllocator");
}

//TODO: Allow shader to be dynamically load and discard later.
void D3D12RHI::LoadAssets()
{
	//Create Root Signature
	m_pD3D12RootSignature = std::make_unique<D3D12RootSignature>();
	ThrowIfFailed(m_pD3D12RootSignature->CreateRootSignature(m_pD3D12Device->GetDevice()),"Faild to create D3D12RootSignature");

	//Compile and load shader
	ComPtr<ID3DBlob> pVertexShader;
    ComPtr<ID3DBlob> pPixelShader;
	ThrowIfFailed(D3DCompileFromFile(L"Engine/Source/Shader/Default.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &pVertexShader, nullptr), "Faild to Compile VS");
	ThrowIfFailed(D3DCompileFromFile(L"Engine/Source/Shader/Default.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &pPixelShader, nullptr), "Faild to Compile PS");
}
