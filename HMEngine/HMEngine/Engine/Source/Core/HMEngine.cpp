// Copyright (c) 2024 YukiHino. All rights reserved.

#include "../RHI/D3D12/D3D12RHI.h"
#include "HMEngine.h"

//TODO: Forward declaration in class with smart pointers must implement special member functions??
HMEngine::HMEngine() = default;
HMEngine::~HMEngine() = default;

void HMEngine::Initialize()
{
	m_pD3DRHI = std::make_unique<D3D12RHI>();
	m_pD3DRHI->Initialize();
}

void HMEngine::Loop()
{

}

void HMEngine::Terminate()
{

}