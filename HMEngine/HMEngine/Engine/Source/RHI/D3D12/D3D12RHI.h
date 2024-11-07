// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include "../../include/common.h"

class D3D12Adapter;
class D3D12Device;

class D3D12RHI
{
public:
	D3D12RHI();
	~D3D12RHI();

	void Initialize();
	void Update();
	void Render();
	void Destroy();

private:
	u_ptr<D3D12Adapter> m_d3d12Adapter;
	u_ptr<D3D12Device> m_d3d12Device;
};