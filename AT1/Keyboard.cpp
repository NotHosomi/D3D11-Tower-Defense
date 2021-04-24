#include "Keyboard.h"

bool Keyboard::getKey(unsigned char keycode) const noexcept
{
	return keys[keycode];
}

bool Keyboard::getKeyDown(unsigned char keycode) const noexcept
{
	return keys[keycode] && keys[keycode] != keys_prev[keycode];
}

bool Keyboard::getKeyUp(unsigned char keycode) const noexcept
{
	return !keys[keycode] && keys[keycode] != keys_prev[keycode];
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

void Keyboard::endFrame() noexcept
{
	keys_prev = keys;
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

