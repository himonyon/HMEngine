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
            std::cout << e.what() << std::endl;
            std::exit(1);
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
            std::cout << e.what() << std::endl;
            std::exit(1);
        }
    }
}