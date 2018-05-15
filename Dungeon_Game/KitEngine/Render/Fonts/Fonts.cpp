#include "Fonts.h"

using namespace kit;
using namespace kit::Engine;

Font::Font(std::string _str, kit::vec2 _pos) {
	m_str = _str;
	mvec_displayPosition = _pos;
	mf_scale = 1.0f;
	mv_color = DirectX::Colors::White;
}

Font::Font(std::string _str, kit::vec2 _pos, float _scale) {
	m_str = _str;
	mvec_displayPosition = _pos;
	mf_scale = _scale;
	mv_color = DirectX::Colors::White;
}
Font::Font(std::string _str, kit::vec2 _pos, float _scale, DirectX::XMVECTOR _color) {
	m_str = _str;
	mvec_displayPosition = _pos;
	mf_scale = _scale;
	mv_color = _color;
}

Font::Font(Font* _config) {
	m_str = _config->m_str;
	mvec_displayPosition = _config->mvec_displayPosition;
	mf_scale = _config->mf_scale;
	mv_color = _config->mv_color;
}

Font::~Font() {

}

DirectX::XMFLOAT2 Font::GetDisplayPos() {
	return DirectX::XMFLOAT2(mvec_displayPosition.x, mvec_displayPosition.y);
}

void Font::DisplayFont() {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

	// stirng -> wstirng
	std::wstring wstr = cv.from_bytes(m_str);
	std::wcout.imbue(std::locale(""));

	DirectX::XMFLOAT2 origin = { 0,0 };
	g_uptrFonts->DrawString(g_uptrSprites.get(), wstr.c_str(), GetDisplayPos(), mv_color, 0.0f, origin, mf_scale);

}

void Font::DisplayFont(DirectX::XMVECTOR _color) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

	// stirng -> wstirng
	std::wstring wstr = cv.from_bytes(m_str);
	std::wcout.imbue(std::locale(""));

	DirectX::XMFLOAT2 origin = { 0,0 };
	g_uptrFonts->DrawString(g_uptrSprites.get(), wstr.c_str(), GetDisplayPos(), _color, 0.0f, origin, mf_scale);
}

SceneFonts::SceneFonts() {
	mvec_sceneFonts.clear();
}

void SceneFonts::AddFontList(SCENEFONTS _font[], int _max) {
	ClearFontList();
	for (int i = 0; i < _max; ++i) {
		mvec_sceneFonts.push_back(&_font[i].f_fonts);
	}
}

void SceneFonts::MoveFont(int _number, kit::vec2* _pos) {
	mvec_sceneFonts[_number]->MovePosition(_pos);
}

void SceneFonts::ClearFontList() {
	mvec_sceneFonts.clear();
}

void SceneFonts::DisplayFont() {
	for (Font* font : mvec_sceneFonts) {
		font->DisplayFont();
	}
}
