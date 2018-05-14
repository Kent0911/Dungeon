#pragma once

#include <string>
#include <vector>

#include "../../../../KitEngine/Render/Render.h"
#include "../../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../../Configurations/SystemConfiguration/SystemConfiguration.h"

enum class TitleFontList {
	Game_Title,
	Please_push,
	Max
};

typedef struct {
	kit::Engine::Font	f_fonts;
}TITLEFONT;

class TitleFonts {
private:
	std::vector<kit::Engine::Font*> mvec_fonts;

public:
	TitleFonts();
	~TitleFonts();

	void Display();
};
