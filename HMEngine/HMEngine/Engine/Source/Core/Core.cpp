// Copyright (c) 2024 YukiHino. All rights reserved.

#include <Windows.h>

#include "HMEngine.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
    HMEngine::Run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    return 0;
}
