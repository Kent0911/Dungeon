#pragma once

#include <string>
#include <vector>

#include "../../../../KitEngine/Render/Render.h"
#include "../../../../KitEngine/Render/Fonts/Fonts.h"
#include "../../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../../Configurations/SystemConfiguration/SystemConfiguration.h"

enum class TitleFontList {
	Game_Title,
	Please_push,
	Max
};

extern kit::Engine::SCENEFONTS titleFont[static_cast<char>(TitleFontList::Max)];