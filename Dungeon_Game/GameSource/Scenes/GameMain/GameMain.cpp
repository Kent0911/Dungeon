#include "GameMain.h"

GameMain::GameMain() {
	mc_sceneNumber = static_cast<unsigned char>(SCENE::GameMain);
	g_player.GetInstance().SceneNumber(mc_sceneNumber);
}

GameMain::~GameMain() {

}

void GameMain::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void GameMain::Rendar() {
	kit::Engine::g_assetsManager.GetInstance().Render();
}