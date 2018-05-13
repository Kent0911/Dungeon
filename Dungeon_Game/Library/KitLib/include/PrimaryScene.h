#pragma once

//---------------------------------------------------------------------------------------------------
//
// Scene操作の定義
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <memory>

namespace kit {
//---------------------------------------------------------------------------------------------------
//
// Remind:全てのsceneクラスはこのクラスを継承する
//
//---------------------------------------------------------------------------------------------------
	class SceneSystem;

	class Scene {
	protected:
		SceneSystem *mptr_scene_manager;
		unsigned int mi_scene_management;

	public:
		Scene() = default;

		void SetManagerRef(SceneSystem *_ref);
		inline unsigned int SceneManagement() const {
			return mi_scene_management;
		}

		virtual void Update() = 0;
		virtual void Draw() = 0;
	};


//---------------------------------------------------------------------------------------------------
//
// Scene管理を行うクラス
//
//---------------------------------------------------------------------------------------------------

	class SceneSystem {
	private:
		std::shared_ptr<Scene> msptr_current_scene;
		std::shared_ptr<Scene> msptr_previous_scene;

	public:
		SceneSystem() = delete;
		// WARNING:必ず最初に表示するシーンを引数に入れること
		// 引数の入れ方は(std::make_shared<scene>())
		SceneSystem(const std::shared_ptr<Scene> _start_scene);

		// シーンの切り替え関数 引数の入れ方は(std::make_shared<scene>())
		void ChangeScene(const std::shared_ptr<Scene> _change_scene);
		bool UndoChange();

		void Update();
		void Draw();
	};
}