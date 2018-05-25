#include "Tutorial.h"

Tutorial::Tutorial() {
	mc_sceneNumber = static_cast<char>(SCENE::Tutorial);
	g_player.GetInstance().SceneNumber(mc_sceneNumber);
	muptr_filter.reset(new Filter);
	muptr_filter->LoadFile();
}

Tutorial::~Tutorial() {

}

void Tutorial::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void Tutorial::Render() {
	muptr_filter->Render();
	if (muptr_filter->Filtering()) {
		kit::Engine::g_assetsManager.GetInstance().Render();
	}
}