#pragma once
#include <functional>
#include <string>
namespace Leviathan {
	enum class EventType {
		None,
		MouseMove,
		MousePress,
		MouseRelease,
		MouseWheel,

		KeyPress,
		KeyRelease,
		KeyRepeat,
		KeyType,

		WindowRefresh,
		WindowResize,
		WindowMove,
		WindowClose,
		WindowFocus,
		WindowLostFocus
	};

	enum class EventCategory {
		None,
		MouseEvent,
		KeyboardEvent,
		WindowEvent
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategory() const override { return EventCategory::category; }

	class  Event {
	public:
		bool handled = false;
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual EventCategory GetCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

#pragma region Window_Events
	class  RefreshEvent : public Event {
	public:
		RefreshEvent(float frametime) :
			frametime(frametime) {}
		inline float GetFrameTime() { return frametime; }

		EVENT_CLASS_TYPE(WindowRefresh)
			EVENT_CLASS_CATEGORY(WindowEvent)
	private:
		float frametime;
	};

	class  ResizeEvent : public Event {
	public:
		ResizeEvent(int x_size, int y_size) :
			size_x(x_size), size_y(y_size) {}

		inline void GetSize(int* x, int* y) { *x = size_x; *y = size_y; }

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(WindowEvent)
	private:
		int size_x, size_y;
	};

	class  MoveEvent : public Event {
	public:
		MoveEvent(int x, int y) :
			x_pos(x), y_pos(y) {}

		inline void GetPos(int* x, int* y) { *x = this->x_pos; *y = this->y_pos; }

		EVENT_CLASS_TYPE(WindowMove)
			EVENT_CLASS_CATEGORY(WindowEvent)
	private:
		int x_pos, y_pos;
	};

	class  FocusEvent : public Event {
	public:
		FocusEvent(bool focus_state) :
			hasfocus(focus_state) {}

		inline bool hasFocus() { return hasfocus; };

		EVENT_CLASS_TYPE(WindowFocus)
			EVENT_CLASS_CATEGORY(WindowEvent)
	private:
		bool hasfocus;
	};
#pragma endregion

#pragma region Mouse_Events
	class  MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(double pos_x, double pos_y, double delta_x, double delta_y) :
			x_pos(pos_x), y_pos(pos_y), x_delta(delta_x), y_delta(delta_y) {}

		inline void GetPosition(double* x, double* y) { *x = x_pos; *y = y_pos; }
		inline void GetDelta(double* dx, double* dy) { *dx = x_delta; *dy = y_delta; }

		EVENT_CLASS_TYPE(MouseMove)
			EVENT_CLASS_CATEGORY(MouseEvent)
	private:
		double x_pos, y_pos;
		double x_delta, y_delta;
	};

	class  MousePressEvent : public Event {
	public:
		MousePressEvent(int btn) :
			button(btn) {}

		inline int GetButton() { return button; }

		EVENT_CLASS_TYPE(MousePress)
			EVENT_CLASS_CATEGORY(MouseEvent)
	private:
		int button;
	};

	class  MouseReleaseEvent : public Event {
	public:
		MouseReleaseEvent(int btn) :
			button(btn) {}

		inline int GetButton() { return button; }

		EVENT_CLASS_TYPE(MouseRelease)
			EVENT_CLASS_CATEGORY(MouseEvent)
	private:
		int button;
	};

	class  MouseWheelEvent : public Event {
	public:
		MouseWheelEvent(double x, double y) :
			x_scroll(x), y_scroll(y) {}

		inline void GetScroll(double* x, double* y) { *x = x_scroll; *y = y_scroll; }

		EVENT_CLASS_TYPE(MouseWheel)
			EVENT_CLASS_CATEGORY(MouseEvent)
	private:
		double x_scroll, y_scroll;
	};
#pragma endregion

#pragma region Keyboard_Event
	class  KeyPressEvent : public Event {
	public:
		KeyPressEvent(unsigned int key, unsigned int scan, int mds ,bool rep) :
			key_code(key), scan_code(scan), mods(mds), repeat(rep){}

		inline void GetKey(unsigned int* key, unsigned int* scan, int* mds, bool* rep) {
			*key = key_code; 
			*scan = scan_code; 
			*mds = mods; 
			*rep = repeat;
		}

		EVENT_CLASS_TYPE(KeyPress)
			EVENT_CLASS_CATEGORY(KeyboardEvent)
	private:
		unsigned int key_code;
		unsigned int scan_code;
		int mods;
		bool repeat;
	};

	class  KeyReleaseEvent : public Event {
	public:
		KeyReleaseEvent(unsigned int key, unsigned int scan, int mds, bool rep) :
			key_code(key), scan_code(scan), mods(mds), repeat(rep) {}

		inline void GetKey(unsigned int* key, unsigned int* scan, int* mds, bool* rep) {
			*key = key_code;
			*scan = scan_code;
			*mds = mods;
			*rep = repeat;
		}

		EVENT_CLASS_TYPE(KeyRelease)
			EVENT_CLASS_CATEGORY(KeyboardEvent)
	protected:
	private:
		unsigned int key_code;
		unsigned int scan_code;
		int mods;
		bool repeat;
	};

	class  KeyRepeatEvent : public Event {
	public:
		KeyRepeatEvent(int key) :
			repeat_key(key) {}

		inline int GetKey() { return repeat_key; }

		EVENT_CLASS_TYPE(KeyRepeat)
			EVENT_CLASS_CATEGORY(KeyboardEvent)
	protected:
		int repeat_key;
	};

	class  KeyTypeEvent : public Event {
	public:
		KeyTypeEvent(unsigned int key) :
			type_key(key) {}

		inline unsigned int GetKey() { return type_key; }

		EVENT_CLASS_TYPE(KeyType)
			EVENT_CLASS_CATEGORY(KeyboardEvent)
	protected:
		unsigned int type_key;
	};
#pragma endregion

}


