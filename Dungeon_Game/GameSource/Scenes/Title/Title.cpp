#include "Title.h"

Title::Title() {
	mc_sceneNumber = static_cast<unsigned char>(SCENE::Title);
	g_player.GetInstance().SetSceneNumber(mc_sceneNumber);
	mvec_fonts.push_back(kit::Engine::Font(GAME_TITLE, kit::vec2{ g_windowSize.x / 2 , g_windowSize.y / 2 }));
	mvec_fonts.push_back(kit::Engine::Font(std::string("Please push Enter key"), kit::vec2{ 600,600 }, 0.5f));
}

Title::~Title() {
	mvec_fonts.clear();
}

void Title::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void Title::Render() {
	kit::Engine::g_assetsManager.GetInstance().Render();
	for (kit::Engine::Font font : mvec_fonts) {
		font.DisplayFont(DirectX::Colors::White);
	}
}