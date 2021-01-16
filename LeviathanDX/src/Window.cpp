#include "Window.h"
#include <iostream>

bool initialized = false;
WNDCLASSEX native_window_class;
const wchar_t* className = L"BaseWindowClass";

Window::Window()
{
	window_title = L"Window";
	Init();
}

Window::~Window()
{
	if (native_window) {
		CloseWindow(native_window);
		DestroyWindow(native_window);
	}
}

void Window::Init()
{
	if (!initialized) {
		native_window_class = WNDCLASSEX();
		native_window_class.cbSize = sizeof(native_window_class);
		native_window_class.style = CS_OWNDC;
		native_window_class.lpfnWndProc = DefWindowProc;
		native_window_class.cbClsExtra = 0;
		native_window_class.cbWndExtra = 0;
		native_window_class.hInstance = GetModuleHandle(NULL);
		native_window_class.hIcon = nullptr;
		native_window_class.hCursor = nullptr;
		native_window_class.hbrBackground = nullptr;
		native_window_class.lpszMenuName = nullptr;
		native_window_class.lpszClassName = className;
		native_window_class.hIconSm = nullptr;
		RegisterClassEx(&native_window_class);
		initialized = true;
	}
}

void Window::Create(int width, int height, std::string title)
{
	native_window = CreateWindowEx(
		0, 
		className, 
		window_title, 
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		width, 
		height,
		nullptr, 
		nullptr, 
		GetModuleHandle(NULL),
		nullptr);

	if (!native_window) {
		std::cout << "Something went wrong when creating HWND\n";
		return;
	}

	ShowWindow(native_window, SW_SHOW);
}

void Window::Run()
{
	MSG msg = MSG();
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::SetVisibility(bool visible)
{
	if (visible) {
		ShowWindow(native_window, SW_SHOW);
	}
	else {
		ShowWindow(native_window, SW_HIDE);
	}
}


