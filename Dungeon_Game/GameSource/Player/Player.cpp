#include "Player.h"

Player::Player() {
	md_gamePadNumber = mc_devices.mc_gamePad.AssignNumber();
	mc_devices.muptr_keyboard = std::make_unique<DirectX::Keyboard>();
	mc_devices.muptr_mouse = std::make_unique<DirectX::Mouse>();
	mfunc_UpdateFunc = &Player::ControlTitle;
	mc_sceneNumber = START_SCENE_NUMBER;
}

void Player::GameSetUp() {
	switch (mc_selectedDifficulty) {
	case static_cast<char>(DIFFICULTY::Tutorial) :
		StockTorchs(static_cast<char>(DIFFICULTY::Tutorial));
		StockLeadingInsects(static_cast<unsigned char>(DIFFICULTY::Tutorial));
		break;

	case static_cast<char>(DIFFICULTY::Easy) :
		StockTorchs(static_cast<char>(STOCK_TORCHS::Easy));
		StockLeadingInsects(static_cast<char>(STOCK_LEADINGINSECT::Easy));
		break;

	case static_cast<char>(DIFFICULTY::Normal):
		StockTorchs(static_cast<char>(STOCK_TORCHS::Normal));
		StockLeadingInsects(static_cast<char>(STOCK_LEADINGINSECT::Normal));
		break;

	case static_cast<char>(DIFFICULTY::Hard) :
		StockTorchs(static_cast<char>(STOCK_TORCHS::Hard));
		StockLeadingInsects(static_cast<char>(STOCK_LEADINGINSECT::Hard));
		break;
	}
}

void Player::StockTorchs(const unsigned char _num) {
	mc_havingTorchs = _num;
	for (char c = 0; c < mc_havingTorchs; ++c) {
		mvec_torchs.push_back(new Torch);
	}
}

void Player::StockLeadingInsects(const unsigned char _num) {
	mc_havingLeadingInsects = _num;
	for (char c = 0; c < mc_havingLeadingInsects; ++c) {
		mvec_leadingInsects.push_back(new LeadingInsect);
	}
}

char Player::FindUsableTorch() {
	for (char c = 0; mvec_torchs.size(); ++c) {
		if (false == mvec_torchs[c]->IsUsed()) {
			return c;
			break;
		}
	}
}

void Player::ChangeScene(kit::Engine::KitEngine* _engine) {
	switch (mc_sceneNumber) {
	case static_cast<unsigned char>(SCENE::Title) :
		_engine->ChangeScene(std::make_shared<SelectDevice>());
		break;

	case static_cast<unsigned char>(SCENE::SelectDevice) :
		_engine->ChangeScene(std::make_shared<Tutorial>());
		break;

	case static_cast<unsigned char>(SCENE::StartMenu) :
		_engine->ChangeScene(std::make_shared<GameMain>());
		break;
	}
	
}

void Player::ControlTitle(kit::Engine::KitEngine* _engine) {
	// GamePad press start button or Keyboard enter key
	if (static_cast<unsigned int>(kit::GamePad_Buttons::Start) & mc_devices.mc_gamePad.GetState(md_gamePadNumber).wButtons || mc_devices.muptr_keyboard->GetState().Enter) {
		ChangeScene(_engine);
	}
}

void Player::ChangeMode() {
	if (mb_SelectedGamePad) {// true
		if (static_cast<char>(MODE::Player) & mc_changeModeFlag) {
			mfunc_UpdateFunc = &Player::GPControlGameMain;
		}
		if (static_cast<char>(MODE::Torch) & mc_changeModeFlag) {
			mfunc_UpdateFunc = &Player::GPControlTorch;
		}
	}
	else {// false
		if (static_cast<char>(MODE::Player) & mc_changeModeFlag) {
			mfunc_UpdateFunc = &Player::KeyControlGameMain;
		}
		if (static_cast<char>(MODE::Torch) & mc_changeModeFlag) {
			mfunc_UpdateFunc = &Player::KeyControlTorch;
		}
	}
}

void Player::ChangeMode(char _mode) {
	switch (_mode) {
	case static_cast<char>(MODE::Player) :
		mc_changeModeFlag = static_cast<char>(MODE::Player);
		break;

	case static_cast<char>(MODE::Torch) :
		mc_changeModeFlag = static_cast<char>(MODE::Torch);
		break;

	default:
		mc_changeModeFlag = static_cast<char>(MODE::Player);
	}
}

void Player::Jump() {

}

void Player::GPMove() {
	short thumbLX = mc_devices.mc_gamePad.GetState(md_gamePadNumber).sThumbLX;
	if (-GAMEPAD_THRESHOLD > thumbLX) {
		muptr_character->MovePosX(-MOVE_SPEED);
	}
	if (thumbLX > GAMEPAD_THRESHOLD) {
		muptr_character->MovePosY(MOVE_SPEED);
	}
}

void Player::GPControlGameMain(kit::Engine::KitEngine* _engine) {
	GPMove();
	if (static_cast<unsigned int>(kit::GamePad_Buttons::L1) & mc_devices.mc_gamePad.GetState(md_gamePadNumber).wButtons) {
		mc_isActiveTorchsNumber = FindUsableTorch();
		mc_changeModeFlag = static_cast<char>(MODE::Torch);
	}
}

void Player::GPControlTorch(kit::Engine::KitEngine*) {
	mvec_torchs[mc_isActiveTorchsNumber]->GPControl(&mc_devices);
}

void Player::KeyMove() {
	if (mc_devices.muptr_keyboard->GetState().A) {
		muptr_character->MovePosX(-MOVE_SPEED);
	}
	if (mc_devices.muptr_keyboard->GetState().D) {
		muptr_character->MovePosX(MOVE_SPEED);
	}
}

void Player::KeyControlGameMain(kit::Engine::KitEngine* _engine) {
	KeyMove();
	if (mc_devices.muptr_keyboard->GetState().T) {
		mc_isActiveTorchsNumber = FindUsableTorch();
		mc_changeModeFlag = static_cast<char>(MODE::Torch);
	}
}

void Player::KeyControlTorch(kit::Engine::KitEngine*) {
	mvec_torchs[mc_isActiveTorchsNumber]->KeyControl(&mc_devices);
}

void Player::Update(kit::Engine::KitEngine* _engine) {
	if (static_cast<char>(SCENE::Title) != mc_sceneNumber || static_cast<char>(SCENE::SelectDevice) != mc_sceneNumber) {
		ChangeMode();
	}
	(this->*mfunc_UpdateFunc)(_engine);
}