// Copyright (c) 2024 YukiHino. All rights reserved.
#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

struct ID3D12Device;
struct ID3D12PipelineState;

class D3D12PipelineStateObject
{
public:
	bool CreatePipelineStateObject(ComPtr<ID3D12Device> pDevice, ComPtr<ID3D12RootSignature> pRootSignature);

	ComPtr<ID3D12PipelineState> GetPipelineState();

private:
	ComPtr<ID3D12PipelineState> m_pPipelineState;
};
