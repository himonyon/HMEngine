// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class HMEngine
{
public:
	static int Run(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nCmdShow);
	static int Loop();
	static void Terminate();

	static HWND GetWnd();

private:
	static HWND m_hwnd;
};