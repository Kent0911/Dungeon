#pragma once

#include <d3d11.h>
#include <memory>


#include "../../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../../Player/Player.h"
#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../Library/DirectXTK/include/SimpleMath.h"
#include "TitleFonts\TitleFonts.h"
#include "../../../KitEngine/Render/Fonts/Fonts.h"

extern class TitleFonts;

class Title :public kit::Engine::Scene {
private:

public:
	Title();
	~Title();

	virtual void Update();
	virtual void Render();
};