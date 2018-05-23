#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>

#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Player/Player.h"
#include "../../../KitEngine/Render/Render.h"

class Tutorial :public kit::Engine::Scene {
private:
	std::unique_ptr<ID3D11ShaderResourceView>	 muptr_pd3dTexture;

	HRESULT LoadFile();
public:
	Tutorial();
	~Tutorial();

	virtual void Update();
	virtual void Render();
};