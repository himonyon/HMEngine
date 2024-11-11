// Copyright (c) 2024 YukiHino. All rights reserved.

#include <Windows.h>
#include "../RHI/D3D12/D3D12RHI.h"
#include "HMEngine.h"

HWND HMEngine::m_hwnd = nullptr;

int HMEngine::Run(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
	//CreateWindow
	const wchar_t CLASS_NAME[] = L"HMEngine";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Runtime",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    ShowWindow(m_hwnd, nCmdShow);

	//D3D Initialize
    D3D12RHI* d3d12RHI = new D3D12RHI();;
	d3d12RHI->Initialize();

    //Loop
    MSG msg = {};
    while (true)
    {
        bool isQuit = false;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) isQuit = true;
        }
        if (isQuit)
        {
            Terminate();
            break;
        }

        Loop();
    }

    return 0;
}

int HMEngine::Loop()
{
    return 0;
}

void HMEngine::Terminate()
{

}

HWND HMEngine::GetWnd()
{
    return m_hwnd;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
