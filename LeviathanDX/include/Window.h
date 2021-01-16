#pragma once
#include <Windows.h>
#include <string>
class Window {
public:
	Window();
	~Window();
	void Create(int width, int height, std::string title);
	void Run();


	void SetVisibility(bool visible);
private:
	HWND native_window;
	
	WNDPROC native_proc;

	void Init();
	const wchar_t* window_title;
};