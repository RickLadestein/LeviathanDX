#pragma once
#include <Windows.h>
namespace Leviathan {
	class NativeWindow {
	public:
		NativeWindow();
		~NativeWindow();

		void Close();
		void Destroy();
	protected:
		HWND native_window;
		void HandleMessageQueue();
		virtual void HandleIndividualMessage(MSG& message) {}

		bool shutdownrequested;
	private:
		void CreateNativeWindow();
		static void Init();




	};
}