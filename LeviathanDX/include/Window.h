#pragma once
#include <Windows.h>
#include <string>
#include <wincrypt.h>
class Window {
public:
	Window();
	~Window();
	void Create(int width, int height, std::string title);
	void Run();


	void SetVisibility(bool visible);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);
	void GetPosition(unsigned int* x_pos,unsigned int* y_pos);
	void GetSize(unsigned int* size_x,unsigned int* size_y);
private:
	HWND native_window;
	WNDPROC native_proc;

	void Init();
	const wchar_t* window_title;

	int pos_x, pos_y;
	int width, height;
};