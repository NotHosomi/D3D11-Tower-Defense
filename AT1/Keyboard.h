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