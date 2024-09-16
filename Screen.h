#pragma once
#include "Windows.h"
#include "Eigen/Eigen"
#include <string>

using Eigen::Vector2i;

class Screen
{
public:
	static void Set(unsigned width, unsigned height);
	static void Set(unsigned width, unsigned height, Vector2i offset);
	static void SetTitle(std::string title);
	static void HideCursor();
	static void Render(CHAR_INFO* charInfo);
	
	static HWND GetHandleConsole();
	static Vector2i GetDesktopResolution();
	static Vector2i GetPixelSize();
	static Vector2i GetBufferSize();
	static Vector2i GetFontSize();

private:
	static inline HWND _handleConsole;
	static inline HANDLE _stdHandle;
	static inline Vector2i _pixelSize;
	static inline Vector2i _bufferSize;

	static void Init();
	static void PostInit();
	static Vector2i CalculateConsoleBufferSize();
};
