#include "Title.h"

Title::Title() {
	mc_sceneNumber = static_cast<unsigned char>(SCENE::Title);
	g_player.GetInstance().SetSceneNumber(mc_sceneNumber);
	g_sceneFonts.GetInstance().AddFontList(titleFont, static_cast<int>(TitleFontList::Max));
}

Title::~Title() {
	g_sceneFonts.GetInstance().ClearFontList();
}

void Title::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void Title::Render() {
	kit::Engine::g_assetsManager.GetInstance().Render();
	g_sceneFonts.GetInstance().DisplayFont();
}