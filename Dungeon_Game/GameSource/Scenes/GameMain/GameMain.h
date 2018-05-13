#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>

#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Player/Player.h"

class GameMain :public kit::Engine::Scene {
private:
	double md_gameTime;
public:
	GameMain();
	~GameMain();

	virtual void Update();
	virtual void Rendar();
};