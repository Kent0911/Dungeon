#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>

#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../../Player/Player.h"
#include "../../../KitEngine/Render/Render.h"
#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../Library/DirectXTK/include/SimpleMath.h"

class Title :public kit::Engine::Scene {
private:
	std::vector<kit::Engine::Font>	mvec_fonts;

public:
	Title();
	~Title();

	virtual void Update();
	virtual void Render();
};