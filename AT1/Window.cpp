#include "Window.h"
#include <sstream>
#include "resource.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
	hInst(GetModuleHandle(nullptr))
{

	// register class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Window::Window(int width, int height, const char* name) noexcept
{
	this->width = width;
	this->height = height;

	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	DWORD StyleFlags = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU; //investiage further style options
	AdjustWindowRect(&wr, StyleFlags, FALSE); // TODO: exception handling

	hWnd = CreateWindow(
		WindowClass::GetName(), "DirectX go BRRRRRRRR", StyleFlags, 
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	renderer = std::make_unique<Renderer>(hWnd);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::setTitle(const std::string& str)
{
	if (SetWindowText(hWnd, str.c_str()) == 0)
	{
		throw WND_LAST_EXCEPT();
	}
}

std::optional<int> Window::readMsgs()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return static_cast<int>(msg.wParam); // return the exit code
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {}; // No exit code
}

Renderer& Window::getRenderer()
{
	return *renderer;
}

/// WINDOWS PROCEDURES
#pragma region WIN_PROC

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThink));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Invoke member msg handler
LRESULT CALLBACK Window::HandleMsgThink(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
#pragma region KBD events

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!(lParam & (1 << 30)) || kbd.isAutorepeatEnabled())
		{
			kbd.onKeyPressed(static_cast<unsigned int>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		kbd.onKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.onChar(static_cast<unsigned char>(wParam));
		break;
	case WM_KILLFOCUS:
		kbd.clearState();
		// release mouse on loss of focus TODO: why does SetCapture only work for holding-down click
		//ReleaseCapture();
		//mouse.onLeave();
		break;
#pragma endregion
#pragma region Mouse events

	case WM_MOUSEMOVE:
		{
			const POINTS pos = MAKEPOINTS(lParam);
			if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height)
			{
				// in client
				mouse.onMove(pos.x, pos.y);
				if (!mouse.checkInWindow())
				{
					SetCapture(hWnd);
					mouse.onEnter();
				}
			}
			else
			{
				// TODO: find out how to continue tracking without requiring click&drag
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					// I'd rather track without requiring L or R down, but SetCapture doesn't want to help me
					mouse.onMove(pos.x, pos.y);
				}
				else
				{
					ReleaseCapture();
					mouse.onLeave();
				}
			}
			break;
		}
	case WM_LBUTTONDOWN:
		{
			const POINTS pos = MAKEPOINTS(lParam);
			mouse.onMB1Down(pos.x, pos.y);
			SetForegroundWindow(hWnd);
			break;
		}
	case WM_RBUTTONDOWN:
		{
			const POINTS pos = MAKEPOINTS(lParam);
			mouse.onMB2Down(pos.x, pos.y);
			break;
		}
	case WM_LBUTTONUP:
		{
			const POINTS pos = MAKEPOINTS(lParam);
			mouse.onMB1Up(pos.x, pos.y);
			break;
		}
	case WM_RBUTTONUP:
		{
			const POINTS pos = MAKEPOINTS(lParam);
			mouse.onMB2Up(pos.x, pos.y);
			break;
		}
	case WM_MOUSEWHEEL:
		{
			const POINTS pos = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				mouse.onMWheelUp(pos.x, pos.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				mouse.onMWheelDown(pos.x, pos.y);
			}
			break;
		}
#pragma endregion
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
#pragma endregion

/// WINDOW EXCEPTION
#pragma region WND_EXCEPTION

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept :
	MyException(line, file), hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType()
		<< "\n[Error Code] " << GetErrorCode()
		<< "\n[Description] " << GetErrorString()
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr)
{
	char* message_buffer = nullptr;
	DWORD msg_length = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&message_buffer), 0, nullptr);
	if (msg_length == 0)
	{
		return "Unidentified error code";
	}
	std::string error_string = message_buffer;
	LocalFree(message_buffer);
	return error_string;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}

#pragma endregion