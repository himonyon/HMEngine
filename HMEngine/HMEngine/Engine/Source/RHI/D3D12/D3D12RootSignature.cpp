// Copyright (c) 2024 YukiHino. All rights reserved.

#include <d3d12.h>
#include "D3D12RootSignature.h"

bool D3D12RootSignature::CreateRootSignature(ComPtr<ID3D12Device> pDevice)
{
	D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc{};
	desc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
	desc.Desc_1_1.NumParameters = 0;
	desc.Desc_1_1.pParameters = nullptr;
	desc.Desc_1_1.NumStaticSamplers = 0;
	desc.Desc_1_1.pStaticSamplers = nullptr;
	desc.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> pSignature;
	ComPtr<ID3DBlob> pError;
	HRESULT hr;
	if (FAILED(D3D12SerializeVersionedRootSignature(&desc, &pSignature, &pError)))
	{
		return false;
	}
	if (FAILED(pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&m_pRootSignature))))
	{
		return false;
	}

	return true;
}

ComPtr<ID3D12RootSignature> D3D12RootSignature::GetRootSignature()
{
	return m_pRootSignature;
}