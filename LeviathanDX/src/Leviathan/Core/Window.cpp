#include "Leviathan/Core/Window.h"
#include <iostream>
#include <sstream>
#include <inttypes.h>
#include <bitset>
namespace Leviathan {
	Window::Window(int width, int height, std::string title)
	{
		window_title = L"Window";
		SetSize(width, height);
	}

	Window::~Window()
	{
		if (native_window) {
			CloseWindow(native_window);
			DestroyWindow(native_window);
		}
	}



	void Window::Run()
	{
		while (!shutdownrequested)
		{
			HandleMessageQueue();
			//call 
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

	void Window::SetTitle(std::string title)
	{
		if (this->native_window) {
			SetWindowTextA(this->native_window, title.c_str());
		}
		else {
			throw new std::exception("Could not set window title: native window not initialized");
		}
	}

	void Window::GetPosition(unsigned int* x_pos, unsigned int* y_pos)
	{
		if (this->native_window) {
			RECT rect;
			GetWindowRect(native_window, &rect);
			*x_pos = (unsigned int)rect.left;
			*y_pos = (unsigned int)rect.top;
		}
		else {
			throw new std::exception("Could not get window position: native window not initialized");
		}
	}

	void Window::GetSize(unsigned int* size_x, unsigned int* size_y)
	{
		if (this->native_window) {
			RECT rect;
			GetWindowRect(native_window, &rect);
			*size_x = (unsigned int)(rect.right - rect.left);
			*size_y = (unsigned int)(rect.bottom - rect.top);
		}
		else {
			throw new std::exception("Could not get window size: native window not initialized");
		}
	}

	std::string Window::GetTitle()
	{
		if (this->native_window) {
			char title[512];
			GetWindowTextA(this->native_window, title, 512);
			std::stringstream ss;
			ss << title;
			return ss.str();
		}
		else {
			throw new std::exception("Could not set window title: native window not initialized");
		}
	}

	void Window::HandleIndividualMessage(MSG& message)
	{
		switch (message.message) {
		case WM_QUIT:
			shutdownrequested = true;
			break;
		case WM_SETFOCUS:
			std::cout << "Gained focus" << std::endl;
			break;
		case WM_KILLFOCUS:
			std::cout << "Lost focus" << std::endl;
			break;
		case WM_KEYDOWN:
			HandleKeyboardDownMessage(message.wParam, message.lParam);
			break;
		case WM_KEYUP:
			HandleKeyboardUpMessage(message.wParam, message.lParam);
			break;
		case WM_CHAR:
			HandleKeyboardCharMessage(message.wParam, message.lParam);
			break;
		case WM_LBUTTONUP: case WM_XBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP:
			HandleMouseUpMessage(message.wParam, message.lParam);
			break;
		case WM_LBUTTONDOWN: case WM_XBUTTONDOWN: case WM_RBUTTONDOWN: case WM_MBUTTONDOWN:
			HandleMouseUpMessage(message.wParam, message.lParam);
			break;
		}
	}

#pragma region Keyboard_Messages
	void Window::HandleKeyboardUpMessage(WPARAM wparam, LPARAM lparam)
	{
		unsigned int key_code = (unsigned int)wparam;
		uint16_t repeat_count = (lparam >> 0) & 0xFFFFFFFF;
		uint8_t scan_code = (lparam >> 16) & 0xFFFF;
		bool repeat = (lparam >> 30) & 0xFF;
		Leviathan::KeyPressEvent ev(key_code, scan_code, 0, repeat);
		this->OnKeyPress.Broadcast(ev);

		std::cout << "Keyboard up event[k_code, s_code, repeat]: " << +key_code << ", " << +scan_code << ", " << +repeat << std::endl;
	}

	void Window::HandleKeyboardDownMessage(WPARAM wparam, LPARAM lparam)
	{
		unsigned int key_code = (unsigned int)wparam;
		uint16_t repeat_count = (lparam >> 0) & 0xFFFFFFFF;
		uint8_t scan_code = (lparam >> 16) & 0xFFFF;
		bool repeat = (lparam >> 30) & 0xFF;
		Leviathan::KeyReleaseEvent ev(key_code, scan_code, 0, repeat);
		this->OnKeyRelease.Broadcast(ev);

		std::cout << "Keyboard down event[k_code, s_code, repeat]: " << +key_code << ", " << +scan_code << ", " << +repeat << std::endl;
	}

	void Window::HandleKeyboardCharMessage(WPARAM wparam, LPARAM lparam)
	{
		unsigned int ascii_code = (unsigned int)wparam;
		Leviathan::KeyTypeEvent ev(ascii_code);
		this->OnKeyType.Broadcast(ev);

		std::cout << "Keyboard type event[charcode]: " << (char)ascii_code << std::endl;
	}
#pragma endregion

#pragma region Mouse_Messages
	void Window::HandleMouseDownMessage(WPARAM wparam, LPARAM lparam)
	{
	}

	void Window::HandleMouseUpMessage(WPARAM wparam, LPARAM lparam)
	{
	}

	void Window::HandleMouseMoveMessage(WPARAM wparam, LPARAM lparam)
	{
	}

	void Window::HandleMouseWheelMessage(WPARAM wparam, LPARAM lparam)
	{
	}
#pragma endregion


}





