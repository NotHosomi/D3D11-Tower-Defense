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
#include "Keyboard.h"

bool Keyboard::getKey(unsigned char keycode) const noexcept
{
	return keys[keycode];
}

Keyboard::Event Keyboard::readKey() noexcept
{
	if (key_buffer.size() > 0u)
	{
		Keyboard::Event e = key_buffer.front();
		key_buffer.pop();
		return e;
	}
	return Keyboard::Event();
}

bool Keyboard::isKeyBufferEmpty() const noexcept
{
	return key_buffer.empty();
}

char Keyboard::readChar() noexcept
{
	if (char_buffer.size() > 0u)
	{
		unsigned char charcode = char_buffer.front();
		char_buffer.pop();
		return charcode;
	}
	return 0;
}

bool Keyboard::isCharBufferEmpty() const noexcept
{
	return char_buffer.empty();
}

void Keyboard::flushKeys() noexcept
{
	key_buffer = std::queue<Event>();
}

void Keyboard::flushChars() noexcept
{
	char_buffer = std::queue<char>();
}

void Keyboard::flush() noexcept
{
	flushKeys();
	flushChars();
}

void Keyboard::setAutorepeat(bool state) noexcept
{
	autorepeatEnabled = state;
}

bool Keyboard::isAutorepeatEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::onKeyPressed(unsigned char keycode) noexcept
{
	keys[keycode] = true;
	key_buffer.push(Keyboard::Event(Keyboard::Event::EventType::E_DOWN, keycode));
	while (key_buffer.size() > KEY_BUFFER_MAX)
	{
		key_buffer.pop();
	}
}

void Keyboard::onKeyReleased(unsigned char keycode) noexcept
{
	keys[keycode] = false;
	key_buffer.push(Keyboard::Event(Keyboard::Event::EventType::E_UP, keycode));
	while (key_buffer.size() > KEY_BUFFER_MAX)
	{
		key_buffer.pop();
	}
}

void Keyboard::onChar(char character) noexcept
{
	char_buffer.push(character);
	while (char_buffer.size() > CHAR_BUFFER_MAX)
	{
		char_buffer.pop();
	}
}

void Keyboard::clearState() noexcept
{
	keys.reset();
}

