#include "Tutorial.h"

Tutorial::Tutorial() {
	mc_sceneNumber = static_cast<char>(SCENE::Tutorial);
	g_player.GetInstance().SetSceneNumber(mc_sceneNumber);
}

Tutorial::~Tutorial() {

}

void Tutorial::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void Tutorial::Render() {
	kit::Engine::g_assetsManager.GetInstance().Render();
}