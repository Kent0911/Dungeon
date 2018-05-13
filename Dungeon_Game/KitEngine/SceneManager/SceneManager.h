#pragma once
#include <memory>
#include <iostream>

#include "Scene\Scene.h"
#include "../AssetsManager/AssetsManager.h"

// extern‚ÌŒx‚Ì”ñ•\¦
#pragma warning (disable:4091)

namespace kit {
	namespace Engine {

		extern class Scene;
		extern AssetsManager g_assetsManager;

		class SceneManager{
		private:
			std::shared_ptr<Scene> msptr_currentScene;
			std::shared_ptr<Scene> msptr_previousScene;

		public:
			SceneManager(std::shared_ptr<Scene> _startScene);
			void ChangeScene(const std::shared_ptr<Scene> _changeScene);
			bool UndoChange();
			inline unsigned char CurrentSceneNumber() const {
//				msptr_currentScene->GetSceneNumber();
			}

			void Update();
			void Render();
		};
	}
}