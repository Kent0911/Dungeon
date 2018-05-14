#pragma once

#include <vector>

#include "../../../KitEngine/Render/Render.h"
#include "../../../Library/KitLib/include/Kitlib.h"

typedef struct {
	kit::Engine::Font f_fonts;
}SCENEFONTS;

class SceneFonts :public kit::Singleton<SceneFonts> {
private:
	friend class kit::Singleton<SceneFonts>;
	SceneFonts();

	std::vector<kit::Engine::Font*> mvec_sceneFonts;

public:
	void AddFontList(SCENEFONTS _font[], int _max);
	void ClearFontList();
	void DisplayFont();
};

//--------------------------------------------------------------------------------------------------------------------------------------------
//
// シーンのフォント表示で使用するグローバル変数
//
//--------------------------------------------------------------------------------------------------------------------------------------------
extern SceneFonts g_sceneFonts;
