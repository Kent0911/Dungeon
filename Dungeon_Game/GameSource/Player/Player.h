#pragma once

#include <d3d11.h>
#include <memory>
#include <vector>

#include "../../Library/KitLib/include/Kitlib.h"
#include "../GameObjects/Torch/Torch.h"
#include "../GameObjects/LeadingInsect/LeadingInsect.h"
#include "../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../KitEngine/SceneManager/Scene/Scene.h"
#include "../../KitEngine/KitEngine.h"
#include "../../Library/DirectXTK/include/Mouse.h"
#include "../../Library/DirectXTK/include/Keyboard.h"
#include "../GameObjects/Character/Character.h"
#include "../GameObjects/Camera/Camera.h"
#include "../Scenes/GameMain/Tutorial/Tutorial.h"
#include "../Scenes/SelectDevice/SelectDevice.h"
#include "../Scenes/GameMain/GameMain.h"

extern class Torch;

#pragma warning (disable:0312)


enum class MODE :unsigned char {
	Player = (1 << 0),
	Torch = (1 << 1),
	Leadinginsect = (1 << 2),
};

class Devices {
public:
	kit::GamePad						mc_gamePad;
	std::unique_ptr<DirectX::Mouse>		muptr_mouse;
	std::unique_ptr<DirectX::Keyboard>	muptr_keyboard;
};

class Player :public kit::Singleton<Player> {
private:
	friend class kit::Singleton<Player>;
	Player();

	Devices								mc_devices;
	bool								mb_SelectedGamePad;
	DWORD								md_gamePadNumber;

	std::unique_ptr<Character>			muptr_character;
	std::unique_ptr<Camera>				muptr_camera;
	unsigned char						mc_selectedDifficulty;
	std::weak_ptr<kit::Engine::Scene>	mwptr_currentScene;
	std::vector<Torch*>					mvec_torchs;
	char								mc_isActiveTorchsNumber;
	char								mc_havingTorchs;
	std::vector<LeadingInsect*>			mvec_leadingInsects;
	char								mc_havingLeadingInsects;

	char								mc_changeModeFlag;
	unsigned char						mc_sceneNumber;

	void(Player::*mfunc_updateFunc)(kit::Engine::KitEngine*);

	void GameSetup();
	void StockTorchs(const unsigned char _num);
	void StockLeadingInsects(const unsigned char _num);

	char FindUsableTorch();

	void ChangeScene(kit::Engine::KitEngine* _engine);
	
	void ControlTitle(kit::Engine::KitEngine* _engine);
	void ControlSelectDevice(kit::Engine::KitEngine* _engine);

	void ChangeMode();
	void Jump();
	void PadMove();
	void PadControlGameMain(kit::Engine::KitEngine* _engine);
	void PadControlTorch(kit::Engine::KitEngine*);
	void KeyMove();
	void KeyControlGameMain(kit::Engine::KitEngine* _engine);
	void KeyControlTorch(kit::Engine::KitEngine*);
public:
	void ChangeMode(char _mode);
	inline DWORD GetDword() const {
		return md_gamePadNumber;
	}
	inline void SceneNumber(const char _sceneNumber) {
		mc_sceneNumber = _sceneNumber;
	}
	inline char SceneNumber() const {
		return mc_sceneNumber;
	}
	inline void SetModeFlag(const char _flag) {
		mc_changeModeFlag = _flag;
	}
	inline void SetDevice(const bool _flag) {
		mb_SelectedGamePad = _flag;
	}
	inline void SubTorchsCounts() {
		mc_havingTorchs--;
	}
	inline void SubLeadingInsectsCounts() {
		mc_havingLeadingInsects--;
	}
	inline Devices* GetDevicesState(){
		return &mc_devices;
	}
	void Update(kit::Engine::KitEngine* _engine);
};

