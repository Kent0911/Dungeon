#include "SceneManager.h"

using namespace kit;
using namespace Engine;

SceneManager::SceneManager(std::shared_ptr<Scene> _startScene) {
	msptr_currentScene = _startScene;
	msptr_currentScene->SetManagerRef(this);
	msptr_previousScene = nullptr;
}

void SceneManager::ChangeScene(const std::shared_ptr<Scene> _changeScene) {
	g_assetsManager.GetInstance().ClearAssets();
	msptr_previousScene = msptr_currentScene;
	msptr_currentScene = _changeScene;
	msptr_currentScene->SetManagerRef(this);

}

bool SceneManager::UndoChange() {
	if (nullptr != msptr_previousScene) {
		msptr_currentScene = msptr_previousScene;
		msptr_previousScene = msptr_currentScene;
		return true;
	}
	else { return false; }
}

void SceneManager::Update() {
	msptr_currentScene->Update();
}

void SceneManager::Render() {
	msptr_currentScene->Render();
}