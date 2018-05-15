#include "SelectDeviceFonts.h"

kit::Engine::SCENEFONTS selectDeviceFont[static_cast<char>(SelectDeviceFontList::Max)]{
	{	kit::Engine::Font("Please select using device(s)",	kit::vec2(g_windowSize.x / 2 - 200 ,100),	1.0f,	DirectX::Colors::White) },
	{	kit::Engine::Font("GamePad",						kit::vec2(g_windowSize.x / 2 - 200 ,200),	0.7f)	},
	{	kit::Engine::Font("Keyboard and mouse",				kit::vec2(g_windowSize.x / 2 - 200 ,300),	0.7f )	},
	{	kit::Engine::Font("->",								kit::vec2(g_windowSize.x / 2 - 250, 200),	0.7f,	DirectX::Colors::Red)		}
};