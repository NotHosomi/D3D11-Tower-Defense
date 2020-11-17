#include "Mouse.h"


std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x,y };
}

int Mouse::getX() const noexcept
{
	return x;
}

int Mouse::getY() const noexcept
{
	return y;
}

bool Mouse::getM1() const noexcept
{
	return m1;
}

bool Mouse::getM2() const noexcept
{
	return m2;
}

bool Mouse::checkInWindow() const noexcept
{
	return in_bounds;
}

Mouse::Event Mouse::fetchEvent() noexcept
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	return Mouse::Event();
}

bool Mouse::IsEmpty() const noexcept
{
	return buffer.empty();
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::onMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.push(Mouse::Event(Mouse::Event::EventType::E_MOVE, *this));
	truncateBuffer();
}

void Mouse::onMB1Down(int x, int y) noexcept
{
	m1 = true;

	buffer.push(Mouse::Event(Mouse::Event::EventType::E_LDOWN, *this));
	truncateBuffer();
}

void Mouse::onMB1Up(int x, int y) noexcept
{
	m1 = false;

	buffer.push(Mouse::Event(Mouse::Event::EventType::E_LUP, *this));
	truncateBuffer();
}

void Mouse::onMB2Down(int x, int y) noexcept
{
	m2 = true;

	buffer.push(Mouse::Event(Mouse::Event::EventType::E_R_DOWN, *this));
	truncateBuffer();
}

void Mouse::onMB2Up(int x, int y) noexcept
{
	m2 = false;

	buffer.push(Mouse::Event(Mouse::Event::EventType::E_R_UP, *this));
	truncateBuffer();
}

void Mouse::onMWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::EventType::E_WHEEL_UP, *this));
	truncateBuffer();
}

void Mouse::onMWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::EventType::E_WHEEL_DOWN, *this));
	truncateBuffer();
}

void Mouse::onLeave() noexcept
{
	in_bounds = false;
	buffer.push(Mouse::Event(Mouse::Event::EventType::E_LEAVE, *this));
	truncateBuffer();
}

void Mouse::onEnter() noexcept
{
	in_bounds = true;
	buffer.push(Mouse::Event(Mouse::Event::EventType::E_ENTER, *this));
	truncateBuffer();
}

void Mouse::truncateBuffer() noexcept
{
	while (buffer.size() > BUFFER_SIZE)
	{
		buffer.pop();
	}
}