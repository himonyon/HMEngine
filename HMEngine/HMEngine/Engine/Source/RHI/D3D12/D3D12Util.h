// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include <iostream>
#include <stdexcept>

//COM Exception
inline void ThrowIfFailed(HRESULT hr, std::string errorMessage)
{
    if (FAILED(hr))
    {
        try
        {
            throw std::runtime_error(errorMessage);
        }
        catch(const std::runtime_error& e)
        {
            _RPT0(_CRT_ERROR, e.what());
        }
    }
}

inline void ThrowIfFailed(bool result, std::string errorMessage)
{
    if (!result)
    {
        try
        {
            throw std::runtime_error(errorMessage);
        }
        catch(const std::runtime_error& e)
        {
            _RPT0(_CRT_ERROR, e.what());
        }
    }
}