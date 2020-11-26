/******************************************************************************************
*	Chili Direct3D Engine																  *
*	Copyright 2018 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of Chili Direct3D Engine.											  *
*																						  *
*	Chili Direct3D Engine is free software: you can redistribute it and/or modify		  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili Direct3D Engine is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili Direct3D Engine.  If not, see <http://www.gnu.org/licenses/>.    *
******************************************************************************************/
#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class EventType
		{
			E_DOWN,
			E_UP,
			E_INVALID
		};
	private:
		EventType type;
		unsigned char code;
	public:
		Event() : type(EventType::E_INVALID), code(0u)
		{}
		Event(EventType type, unsigned char code) noexcept :
			type(type), code(code)
		{}
		bool IsPress() const noexcept
		{ return type == EventType::E_DOWN; }
		bool IsRelease() const noexcept
		{ return type == EventType::E_UP; }
		bool IsValid() const noexcept
		{ return type != EventType::E_INVALID; }
		unsigned char GetCode() const noexcept
		{ return code; }
	};
	// constructors
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	// keys
	bool getKey(unsigned char keycode) const noexcept;
	bool getKeyDown(unsigned char keycode) const noexcept;
	bool getKeyUp(unsigned char keycode) const noexcept;
	Event readKey() noexcept;
	bool isKeyBufferEmpty() const noexcept;
	void flushKeys() noexcept;
	// chars
	char readChar() noexcept;
	bool isCharBufferEmpty() const noexcept;
	void flushChars() noexcept;

	// utils
	void flush() noexcept;
	void setAutorepeat(bool state) noexcept;
	bool isAutorepeatEnabled() const noexcept;
	void endFrame() noexcept;
private:
	void onKeyPressed(unsigned char keycode) noexcept;
	void onKeyReleased(unsigned char keycode) noexcept;
	void onChar(char character) noexcept;
	void clearState() noexcept;

	static constexpr unsigned int NUM_KEYS = 256u;
	static constexpr unsigned int KEY_BUFFER_MAX = 16u;
	static constexpr unsigned int CHAR_BUFFER_MAX = 16u;

	bool autorepeatEnabled = false;

	std::bitset<NUM_KEYS> keys;
	std::bitset<NUM_KEYS> keys_prev;
	std::queue<Event> key_buffer;
	std::queue<char> char_buffer;
};