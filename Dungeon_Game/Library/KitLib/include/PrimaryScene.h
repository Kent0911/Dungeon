#pragma once

//---------------------------------------------------------------------------------------------------
//
// Scene����̒�`
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <memory>

namespace kit {
//---------------------------------------------------------------------------------------------------
//
// Remind:�S�Ă�scene�N���X�͂��̃N���X���p������
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
// Scene�Ǘ����s���N���X
//
//---------------------------------------------------------------------------------------------------

	class SceneSystem {
	private:
		std::shared_ptr<Scene> msptr_current_scene;
		std::shared_ptr<Scene> msptr_previous_scene;

	public:
		SceneSystem() = delete;
		// WARNING:�K���ŏ��ɕ\������V�[���������ɓ���邱��
		// �����̓������(std::make_shared<scene>())
		SceneSystem(const std::shared_ptr<Scene> _start_scene);

		// �V�[���̐؂�ւ��֐� �����̓������(std::make_shared<scene>())
		void ChangeScene(const std::shared_ptr<Scene> _change_scene);
		bool UndoChange();

		void Update();
		void Draw();
	};
}