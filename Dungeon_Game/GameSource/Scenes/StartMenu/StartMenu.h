#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>

#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Player/Player.h"

class StartMenu :public kit::Engine::Scene {
private:
	char mc_selectDifficulty;

public:
	StartMenu();
	~StartMenu();

	virtual void Update();
	virtual void Render();
};