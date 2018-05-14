#pragma once

#include <memory>
#include <vector>

#include "../../../../KitEngine/Render/Render.h"
#include "../../../Configurations/GameConfiguration/GameConfiguration.h"


enum class SelectDeviceFontList {
	Please_select,
	GamePad,
	KeyboardAndMouse,
	Max
};

typedef struct {
	kit::Engine::Font f_fonts;
}SELECTDEVICEFONT;
