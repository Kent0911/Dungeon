#pragma once

#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>

#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../../Player/Player.h"
#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../Library/DirectXTK/include/SimpleMath.h"
#include "TitleFonts\TitleFonts.h"

extern class TitleFonts;

class Title :public kit::Engine::Scene {
private:
	TitleFonts*	mf_title;

public:
	Title();
	~Title();

	virtual void Update();
	virtual void Render();
};