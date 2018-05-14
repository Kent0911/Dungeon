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
// �V�[���̃t�H���g�\���Ŏg�p����O���[�o���ϐ�
//
//--------------------------------------------------------------------------------------------------------------------------------------------
extern SceneFonts g_sceneFonts;
