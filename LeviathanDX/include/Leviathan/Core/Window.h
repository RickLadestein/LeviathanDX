#pragma once
#include "NativeWindow.h"
#include "Leviathan/Util/MultiDelegate.h"
#include "Leviathan/Core/Event.h"
#include <string>
namespace Leviathan {
#pragma region Event_F
	typedef void WindowMoveFn(Leviathan::MoveEvent& ev);
	typedef void WindowResizeFn(Leviathan::ResizeEvent& ev);
	typedef void WindowFocusFn(Leviathan::FocusEvent& ev);
	typedef void WindowRefreshFn(Leviathan::RefreshEvent& ev);

	typedef void MousePressFn(Leviathan::MousePressEvent& ev);
	typedef void MouseReleaseFn(Leviathan::MouseReleaseEvent& ev);
	typedef void MouseWheelFn(Leviathan::MouseWheelEvent& ev);
	typedef void MouseMoveFn(Leviathan::MouseMoveEvent& ev);

	typedef void KeyPressFn(Leviathan::KeyPressEvent& ev);
	typedef void KeyReleaseFn(Leviathan::KeyReleaseEvent& ev);
	typedef void KeyTypeFn(Leviathan::KeyTypeEvent& ev);
#pragma endregion

	class Window : public NativeWindow {
	public:
		Window(int width, int height, std::string title);
		~Window();
		void Run();

		MultiDelegate<WindowMoveFn> OnWindowMove;
		MultiDelegate<WindowResizeFn> OnWindowResize;
		MultiDelegate<WindowFocusFn> OnWindowFocus;
		MultiDelegate<WindowRefreshFn> OnWindowRefresh;

		MultiDelegate<MousePressFn> OnMousePress;
		MultiDelegate<MouseReleaseFn> OnMouseRelease;
		MultiDelegate<MouseWheelFn> OnMouseWheel;
		MultiDelegate<MouseMoveFn> OnMouseMove;

		MultiDelegate<KeyPressFn> OnKeyPress;
		MultiDelegate<KeyReleaseFn> OnKeyRelease;
		MultiDelegate<KeyTypeFn> OnKeyType;

		void SetVisibility(bool visible);
		void SetPosition(int x, int y);
		void SetSize(int width, int height);
		void SetTitle(std::string title);
		void GetPosition(unsigned int* x_pos, unsigned int* y_pos);
		void GetSize(unsigned int* size_x, unsigned int* size_y);
		std::string GetTitle();
	private:
		void HandleIndividualMessage(MSG& message) override;

		const wchar_t* window_title;
		int pos_x, pos_y;
		int width, height;

		void HandleKeyboardUpMessage(WPARAM wparam, LPARAM lparam);
		void HandleKeyboardDownMessage(WPARAM wparam, LPARAM lparam);
		void HandleKeyboardCharMessage(WPARAM wparam, LPARAM lparam);

		void HandleMouseDownMessage(WPARAM wparam, LPARAM lparam);
		void HandleMouseUpMessage(WPARAM wparam, LPARAM lparam);
		void HandleMouseMoveMessage(WPARAM wparam, LPARAM lparam);
		void HandleMouseWheelMessage(WPARAM wparam, LPARAM lparam);

	};
}