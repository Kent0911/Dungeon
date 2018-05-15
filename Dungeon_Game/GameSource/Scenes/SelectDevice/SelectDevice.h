#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>

#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../../../KitEngine/Render/Render.h"
#include "../../../KitEngine/Render/Fonts/Fonts.h"
#include "SelectDeviceFonts\SelectDeviceFonts.h"

class SelectDevice :public kit::Engine::Scene {
private:
	char	mc_selectDevice;

public:
	SelectDevice();
	~SelectDevice();

	virtual void Update();
	virtual void Render();
};
