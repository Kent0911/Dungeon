#include "SceneFonts.h"

SceneFonts::SceneFonts() {
	mvec_sceneFonts.clear();
}

void SceneFonts::AddFontList(SCENEFONTS _font[], int _max) {
	for (int i = 0; i < _max; ++i) {
		mvec_sceneFonts.push_back(&_font[i].f_fonts);
	}
}

void SceneFonts::ClearFontList() {
	mvec_sceneFonts.clear();
}

void SceneFonts::DisplayFont() {
	for (kit::Engine::Font* font : mvec_sceneFonts) {
		font->DisplayFont(DirectX::Colors::White);
	}
}