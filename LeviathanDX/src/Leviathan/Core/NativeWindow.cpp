#include "Leviathan/Core/NativeWindow.h"
#include <iostream>
#include "WindowsMessageMap.h"
namespace Leviathan {
	bool template_initialized;
	WNDCLASSEX native_window_class;
	DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX;
	const wchar_t* className = L"BaseWindowClass";
	bool focus_changed = false;
	bool has_focus = false;


	MSG last_received_focus_message;
	bool focus_updated = false;
	MSG last_received_size_message;
	bool size_updated = false;
	MSG last_received_pos_message;
	bool pos_updated = false;

	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static WindowsMessageMap mm;
		OutputDebugStringA(mm(msg, lParam, wParam).c_str());
		switch (msg) {
		case WM_CLOSE:
			PostQuitMessage(1);
			break;
		case WM_SETFOCUS:
			last_received_focus_message.message = msg;
			last_received_focus_message.hwnd = hWnd;
			last_received_focus_message.lParam = lParam;
			last_received_focus_message.wParam = wParam;
			focus_updated = true;
			break;
		case WM_KILLFOCUS:
			last_received_focus_message.message = msg;
			last_received_focus_message.hwnd = hWnd;
			last_received_focus_message.lParam = lParam;
			last_received_focus_message.wParam = wParam;
			focus_updated = true;
			break;
		case WM_SIZE:
			last_received_size_message.message = msg;
			last_received_size_message.hwnd = hWnd;
			last_received_size_message.lParam = lParam;
			last_received_size_message.wParam = wParam;
			size_updated = true;
			break;
		case WM_MOVE:
			last_received_pos_message.message = msg;
			last_received_pos_message.hwnd = hWnd;
			last_received_pos_message.lParam = lParam;
			last_received_pos_message.wParam = wParam;
			pos_updated = true;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void NativeWindow::Init() {
		if (!template_initialized) {
			native_window_class = WNDCLASSEX();
			native_window_class.cbSize = sizeof(native_window_class);
			native_window_class.style = CS_OWNDC;
			native_window_class.lpfnWndProc = WndProc;
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
			template_initialized = true;
		}
	}

	NativeWindow::NativeWindow()
	{
		Init();
		CreateNativeWindow();
	}

	NativeWindow::~NativeWindow()
	{
		Destroy();
	}

	void NativeWindow::Close()
	{
		this->shutdownrequested = true;
	}

	void NativeWindow::Destroy()
	{
		if (native_window) {
			CloseWindow(native_window);
			DestroyWindow(native_window);
		}
	}

	void NativeWindow::HandleMessageQueue()
	{
		MSG msg = MSG();
		BOOL bRet;
		int items_in_queue = PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE);
		while (items_in_queue != 0) {
			bRet = GetMessage(&msg, NULL, 0, 0);
			

			switch (bRet) {
			case -1:
				//Error occured
				std::cerr << "Window error message occured" << std::endl;
				break;
			case 0:
				//Close window and do not process input any further
				this->Close();
				return;
				break;
			default:
				TranslateMessage(&msg);
				HandleIndividualMessage(msg);
				DispatchMessage(&msg);
				break;
			}
			items_in_queue = PeekMessageA(&msg, native_window, 0, 0, PM_NOREMOVE);
		}

		if (focus_updated) {
			HandleIndividualMessage(last_received_focus_message);
			focus_updated = false;
		}

		if (size_updated) {
			HandleIndividualMessage(last_received_size_message);
			size_updated = false;
		}

		if (pos_updated) {
			HandleIndividualMessage(last_received_pos_message);
			pos_updated = false;
		}
	}

	void NativeWindow::CreateNativeWindow()
	{
		native_window = CreateWindowEx(
			0,
			className,
			L"Window",
			window_style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			GetModuleHandle(NULL),
			nullptr);

		if (!native_window) {
			std::cerr << "Something went wrong when creating HWND\n";
		}
		else {
			ShowWindow(native_window, SW_SHOW);
		}
		shutdownrequested = false;
		focus_changed = true;
		has_focus = true;
	}
}


