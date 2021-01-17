#include "Window.h"
#include <iostream>

bool initialized = false;
WNDCLASSEX native_window_class;
const wchar_t* className = L"BaseWindowClass";
DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

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
	this->width = width;
	this->height = height;
	native_window = CreateWindowEx(
		0, 
		className, 
		window_title, 
		window_style,
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
	}
	else {
		ShowWindow(native_window, SW_SHOW);
	}
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

void Window::SetPosition(int x, int y)
{
	if (this->native_window) {
		unsigned int size_x = 0, size_y = 0;
		this->GetSize(&size_x, &size_y);
		SetWindowPos(this->native_window, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	else {
		throw new std::exception("Could not set window position: native window is not initialized");
	}
}

void Window::SetSize(int width, int height)
{
	if (this->native_window) {
		unsigned int pos_x = 0, pos_y = 0;
		this->GetPosition(&pos_x, &pos_y);
		SetWindowPos(this->native_window, HWND_NOTOPMOST, pos_x, pos_y, width, height, SWP_NOZORDER);
	}
	else {
		throw new std::exception("Could not set window position: native window is not initialized");
	}
}

void Window::GetPosition(unsigned int* x_pos, unsigned int* y_pos)
{
	RECT rect;
	GetWindowRect(native_window, &rect);
	*x_pos = (unsigned int)rect.left;
	*y_pos = (unsigned int)rect.top;
}

void Window::GetSize(unsigned int* size_x, unsigned int* size_y)
{
	RECT rect;
	GetWindowRect(native_window, &rect);
	*size_x = (unsigned int)(rect.right - rect.left);
	*size_y = (unsigned int)(rect.bottom - rect.top);
}


