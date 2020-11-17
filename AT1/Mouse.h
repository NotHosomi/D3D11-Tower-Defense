#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class EventType
		{
			E_LDOWN,
			E_LUP,
			E_R_DOWN,
			E_R_UP,
			E_WHEEL_UP,
			E_WHEEL_DOWN,
			E_MOVE,
			E_ENTER,
			E_LEAVE,
			E_INVALID
		};
	private:
		EventType type;
		bool m1;
		bool m2;
		int x;
		int y;
	public:
		Event() noexcept :
			type(EventType::E_INVALID),
			m1(false), m2(false),
			x(0), y(0)
		{}
		Event(EventType type, const Mouse& parent) noexcept : 
			type(type),
			m1(parent.m1), m2(parent.m2),
			x(parent.x), y(parent.y)
		{}
		bool IsValid() const noexcept
		{ return type != EventType::E_INVALID; }
		EventType GetType() const noexcept
		{ return type; }
		std::pair<int, int> GetPos() const noexcept
		{ return{ x,y }; }
		int GetPosX() const noexcept
		{ return x; }
		int GetPosY() const noexcept
		{ return y; }
		bool LeftIsPressed() const noexcept
		{ return m1; }
		bool RightIsPressed() const noexcept
		{ return m2; }
	};

	/// constructors
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	/// Outward interface
	std::pair<int, int> GetPos() const noexcept;
	int getX() const noexcept;
	int getY() const noexcept;
	bool getM1() const noexcept;
	bool getM2() const noexcept;
	bool checkInWindow() const noexcept;
	Event fetchEvent() noexcept;
	bool IsEmpty() const noexcept;
	void Flush() noexcept;
private:
	/// Window interface
	void onMove(int x, int y) noexcept;
	void onMB1Down(int x, int y) noexcept;
	void onMB1Up(int x, int y) noexcept;
	void onMB2Down(int x, int y) noexcept;
	void onMB2Up(int x, int y) noexcept;
	// TODO: add M3
	void onMWheelUp(int x, int y) noexcept;
	void onMWheelDown(int x, int y) noexcept;
	// TODO: wheel delta
	void onLeave() noexcept;
	void onEnter() noexcept;
	void truncateBuffer() noexcept;

	static constexpr unsigned int BUFFER_SIZE = 16u;
	int x;
	int y;
	bool m1 = false;
	bool m2 = false;
	bool in_bounds = false;
	std::queue<Event> buffer;
};