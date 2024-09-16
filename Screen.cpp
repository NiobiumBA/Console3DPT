#include "Screen.h"


void Screen::Init()
{
	_handleConsole = GetConsoleWindow();
	_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Screen::PostInit()
{
	_bufferSize = CalculateConsoleBufferSize();
}

void Screen::Set(unsigned width, unsigned height)
{
	Init();

	Vector2i fontSize = GetFontSize();

	_pixelSize = Vector2i(width, height).cwiseProduct(fontSize) - Vector2i::Constant(5);

	//Set window to the center of display
	Vector2i display = GetDesktopResolution();
	Vector2i offset = (display - _pixelSize) / 2;

	MoveWindow(_handleConsole, offset.x(), offset.y(), _pixelSize.x(), _pixelSize.y(), true);

	PostInit();

	//COORD bufferSize = { width, height };
	//SetConsoleScreenBufferSize(hWnd, bufferSize);
}

void Screen::Set(unsigned width, unsigned height, Vector2i offset)
{
	Init();

	Vector2i fontSize = GetFontSize();

	_pixelSize = Vector2i(width, height).cwiseProduct(fontSize);

	MoveWindow(_handleConsole, offset.x(), offset.y(), _pixelSize.x(), _pixelSize.y(), true);

	PostInit();
}

void Screen::SetTitle(std::string title)
{
	SetConsoleTitleA(title.c_str());
}

void Screen::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo{10, false};

	SetConsoleCursorInfo(_stdHandle, &cursorInfo);
}

Vector2i Screen::GetDesktopResolution()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	return Vector2i(desktop.right, desktop.bottom);
}

Vector2i Screen::GetPixelSize()
{
	return _pixelSize;
}

Vector2i Screen::GetBufferSize()
{
	return _bufferSize;
}

Vector2i Screen::GetFontSize()
{
	CONSOLE_FONT_INFO fontInfo;

	GetCurrentConsoleFont(_stdHandle, false, &fontInfo);

	return Vector2i(fontInfo.dwFontSize.X, fontInfo.dwFontSize.Y);
}

Vector2i Screen::CalculateConsoleBufferSize()
{
	CONSOLE_SCREEN_BUFFER_INFO info = {};
	GetConsoleScreenBufferInfo(_stdHandle, &info);
	return Vector2i(info.srWindow.Right, info.srWindow.Bottom + 1);
}

void Screen::Render(CHAR_INFO* charInfo)
{
	COORD sizeOutput = { (short)_bufferSize.x(), (short)_bufferSize.y() };
	SMALL_RECT outputRect = { 0, 0, sizeOutput.X, sizeOutput.Y };
	WriteConsoleOutput(_stdHandle, charInfo, sizeOutput, { 0, 0 }, &outputRect);
}

HWND Screen::GetHandleConsole()
{
	return _handleConsole;
}
