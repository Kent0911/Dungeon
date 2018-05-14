#include "TitleFonts.h"

TITLEFONT TitleFont[static_cast<int>(TitleFontList::Max)]{
	{	kit::Engine::Font("Dungeon_Game",kit::vec2{g_windowSize.x / 2 ,g_windowSize.y / 2})		},
	
	{	kit::Engine::Font("Plase push Enter key or GamePad's Start button",kit::vec2{ 100,600 },0.5f)	 }
};

TitleFonts::TitleFonts() {
	for (int i = 0; i != static_cast<int>(TitleFontList::Max); ++i) {
		mvec_fonts.push_back(&TitleFont[i].f_fonts);
	}
}

TitleFonts::~TitleFonts() {
	mvec_fonts.clear();
}

void TitleFonts::Display() {
	for (int i = 0; i < static_cast<int>(TitleFontList::Max); ++i) {
		mvec_fonts[i]->DisplayFont(DirectX::Colors::White);
	}
}