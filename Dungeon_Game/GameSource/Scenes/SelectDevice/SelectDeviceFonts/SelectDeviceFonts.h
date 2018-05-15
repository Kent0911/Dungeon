#pragma once

#include <memory>
#include <vector>

#include "../../../../KitEngine/Render/Render.h"
#include "../../../../KitEngine/Render/Fonts/Fonts.h"
#include "../../../Configurations/GameConfiguration/GameConfiguration.h"


enum class SelectDeviceFontList {
	Please_select,
	GamePad,
	KeyboardAndMouse,
	Max
};

extern kit::Engine::SCENEFONTS selectDeviceFont[static_cast<char>(SelectDeviceFontList::Max)];