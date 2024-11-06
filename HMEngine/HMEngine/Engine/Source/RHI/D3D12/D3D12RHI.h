// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

class D3D12RHI
{
public:
	void Initialize();
	void Update();
	void Render();
	void Destroy();

private:
	ComPtr<ID3D12Device> m_device;
};