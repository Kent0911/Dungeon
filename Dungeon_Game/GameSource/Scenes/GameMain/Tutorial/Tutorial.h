#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>

#include "../../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../../Player/Player.h"
#include "../../../../KitEngine/Render/Render.h"
#include "../Filter/Filter.h"

extern class Filter;

class Tutorial :public kit::Engine::Scene {
private:
	std::unique_ptr<Filter>	 muptr_filter;

public:
	Tutorial();
	~Tutorial();

	virtual void Update();
	virtual void Render();
};