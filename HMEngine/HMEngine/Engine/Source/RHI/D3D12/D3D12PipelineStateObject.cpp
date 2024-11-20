// Copyright (c) 2024 YukiHino. All rights reserved.

#include <d3d12.h>
#include <d3dcompiler.h>
#include "D3D12PipelineStateObject.h"


bool D3D12PipelineStateObject::CreatePipelineStateObject(ComPtr<ID3D12Device> pDevice, ComPtr<ID3D12RootSignature> pRootSignature)
{
	//Compile and load shader
	ComPtr<ID3DBlob> pVertexShader;
    ComPtr<ID3DBlob> pPixelShader;
	if (FAILED(D3DCompileFromFile(L"Engine/Source/Shader/Default.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &pVertexShader, nullptr)))
	{
		return false;
	}
	if (FAILED(D3DCompileFromFile(L"Engine/Source/Shader/Default.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &pPixelShader, nullptr)))
	{
		return false;
	}

	D3D12_INPUT_ELEMENT_DESC inuptElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};

	//State of Blend
	D3D12_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = false;
	blendDesc.RenderTarget[0].LogicOpEnable = false;
	blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//State of Rasterizer
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	rasterizerDesc.FrontCounterClockwise = false; 
	rasterizerDesc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
	rasterizerDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	rasterizerDesc.DepthClipEnable = true; 
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.ForcedSampleCount = 0;
	rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	//State of DepthStencil
	D3D12_DEPTH_STENCIL_DESC stencilDesc{};
	stencilDesc.DepthEnable = false;
	stencilDesc.StencilEnable = false;

	//PSO
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc{};
	psoDesc.pRootSignature = pRootSignature.Get();
	psoDesc.VS = { reinterpret_cast<UINT8*>(pVertexShader->GetBufferPointer()), pVertexShader->GetBufferSize() };
	psoDesc.PS = { reinterpret_cast<UINT8*>(pPixelShader->GetBufferPointer()), pPixelShader->GetBufferSize() };
	psoDesc.BlendState = blendDesc;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.RasterizerState = rasterizerDesc;
	psoDesc.DepthStencilState = stencilDesc;
	psoDesc.InputLayout = { inuptElementDesc, _countof(inuptElementDesc)};
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.NodeMask = 0;
	if (FAILED(pDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pPipelineState))))
	{
		return false;
	}

	return true;
}

ComPtr<ID3D12PipelineState> D3D12PipelineStateObject::GetPipelineState()
{
	return m_pPipelineState;
}