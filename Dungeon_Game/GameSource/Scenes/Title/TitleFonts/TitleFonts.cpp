#include "TitleFonts.h"

kit::Engine::SCENEFONTS titleFont[static_cast<char>(TitleFontList::Max)]{
	{	kit::Engine::Font("Dungeon_Game",kit::vec2{g_windowSize.x / 2 ,g_windowSize.y / 2})		},

	{	kit::Engine::Font("Plase press Enter key or GamePad's Start button",kit::vec2{ 100,600 },0.5f)	}
};

