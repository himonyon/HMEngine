// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include "../include/common.h"

class D3D12RHI;
class HMEngine
{
public:
	HMEngine();
	~HMEngine();

	void Initialize();
	void Loop();
	void Terminate();

private: 
	u_ptr<D3D12RHI> m_pD3DRHI;
};