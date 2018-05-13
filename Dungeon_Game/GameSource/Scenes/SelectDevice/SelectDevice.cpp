#include "SelectDevice.h"

SelectDevice::SelectDevice() {
	mc_sceneNumber = static_cast<char>(SCENE::SelectDevice);
	g_player.GetInstance().SetSceneNumber(mc_sceneNumber);
}

SelectDevice::~SelectDevice() {

}

void SelectDevice::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void SelectDevice::Render() {
	kit::Engine::g_assetsManager.GetInstance().Render();
}