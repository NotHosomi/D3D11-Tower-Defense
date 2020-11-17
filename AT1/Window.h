#pragma once
#include <Windows.h>
#include <optional>
#include <memory>
#include "MyException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Renderer.h"

class Window
{
public:
	// Classes
	class Exception : public MyException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr);
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

	// constructor/destructor
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	
	// Funcs
	void setTitle(const std::string& str);
	static std::optional<int> readMsgs();

	// Components
	Keyboard kbd;
	Mouse mouse;
	Renderer& getRenderer();

private:
	// Classes
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "MyWindow";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
	// Funcs
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThink(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	// Fields
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Renderer> renderer;
};

// exception helper macro
#define WND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr);
#define WND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError());