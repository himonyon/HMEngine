// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include <stdexcept>

//COM Exception
inline void ThrowIfFailed(HRESULT hr, std::string errorMessage)
{
    if (FAILED(hr))
    {
        throw std::runtime_error(errorMessage);
    }
}