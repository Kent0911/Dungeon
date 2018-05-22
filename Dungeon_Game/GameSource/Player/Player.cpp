#include "Player.h"

Player::Player() {
	md_gamePadNumber = mc_devices.mc_gamePad.AssignNumber();
	mc_devices.muptr_keyboard = std::make_unique<DirectX::Keyboard>();
	mc_devices.muptr_mouse = std::make_unique<DirectX::Mouse>();
	mfunc_updateFunc = &Player::ControlTitle;
	mc_sceneNumber = START_SCENE_NUMBER;
}

void Player::GameSetup() {
	muptr_character.reset( new Character() );
	muptr_camera.reset( new Camera() );
	switch (mc_selectedDifficulty) {
		case static_cast<char>(DIFFICULTY::Tutorial) :
			StockTorchs(static_cast<char>(STOCK_TORCHS::Tutorial));
			StockLeadingInsects(static_cast<unsigned char>(STOCK_LEADINGINSECT::Tutorial));
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
		GameSetup();
		break;

	case static_cast<unsigned char>(SCENE::StartMenu) :
		_engine->ChangeScene(std::make_shared<GameMain>());
		break;
	}
	
}

void Player::ControlTitle(kit::Engine::KitEngine* _engine) {
	XINPUT_GAMEPAD padState = mc_devices.mc_gamePad.GetState(md_gamePadNumber);
	DirectX::Keyboard::State keyState = mc_devices.muptr_keyboard->GetState();
	// GamePad press start button or Keyboard enter key
	if (static_cast<unsigned int>( kit::GamePad_Buttons::Start ) & padState.wButtons || keyState.IsKeyDown( DirectX::Keyboard::Enter )) {
		ChangeScene(_engine);
		mfunc_updateFunc = &Player::ControlSelectDevice;
	}
	mc_devices.muptr_keyboard->Reset();
}

void Player::ControlSelectDevice(kit::Engine::KitEngine* _engine) {
	XINPUT_GAMEPAD padState = mc_devices.mc_gamePad.GetState(md_gamePadNumber);
	DirectX::Keyboard::State keyState = mc_devices.muptr_keyboard->GetState();

	if (static_cast<int>(kit::GamePad_Buttons::A) & padState.wButtons || keyState.IsKeyDown( DirectX::Keyboard::Enter )) {
		ChangeScene(_engine);
		if ( static_cast<bool>(DEVICE::GamePad) == mb_SelectedGamePad ) {
			mfunc_updateFunc = &Player::PadControlGameMain;
		}
		else {
			mfunc_updateFunc = &Player::KeyControlGameMain;
		}
	}
}

void Player::ChangeMode() {
	if ( static_cast<bool>(DEVICE::GamePad) == mb_SelectedGamePad ) {
		if ( static_cast<char>(MODE::Player) & mc_changeModeFlag ) {
			mfunc_updateFunc = &Player::PadControlGameMain;
		}
		if ( static_cast<char>(MODE::Torch) & mc_changeModeFlag ) {
			mfunc_updateFunc = &Player::PadControlTorch;
		}
	}
	else {// DEVICE::Keyboard == true
		if ( static_cast<char>(MODE::Player) & mc_changeModeFlag ) {
			mfunc_updateFunc = &Player::KeyControlGameMain;
		}
		if ( static_cast<char>(MODE::Torch) & mc_changeModeFlag ) {
			mfunc_updateFunc = &Player::KeyControlTorch;
		}
	}
}

void Player::ChangeMode(char _mode) {
	switch (_mode) {
	case static_cast<char>(MODE::Player) :
		mc_changeModeFlag = static_cast<char>(MODE::Player);
		ChangeMode();
		break;

	case static_cast<char>(MODE::Torch) :
		mc_changeModeFlag = static_cast<char>(MODE::Torch);
		ChangeMode();
		break;

	default:
		mc_changeModeFlag = static_cast<char>(MODE::Player);
		ChangeMode();
	}
}

void Player::Jump() {

}

void Player::PadMove() {
	short thumbLX = mc_devices.mc_gamePad.GetState(md_gamePadNumber).sThumbLX;
	if (-GAMEPAD_THRESHOLD > thumbLX) {
		muptr_character->MovePosX(-MOVE_SPEED);
	}
	if (thumbLX > GAMEPAD_THRESHOLD) {
		muptr_character->MovePosY(MOVE_SPEED);
	}
}

void Player::PadControlGameMain(kit::Engine::KitEngine* _engine) {
	PadMove();
	if (static_cast<unsigned int>(kit::GamePad_Buttons::L1) & mc_devices.mc_gamePad.GetState(md_gamePadNumber).wButtons) {
		mc_isActiveTorchsNumber = FindUsableTorch();
		ChangeMode(static_cast<char>(MODE::Torch));
	}
	muptr_camera->Update();
}

void Player::PadControlTorch(kit::Engine::KitEngine*) {
	mvec_torchs[mc_isActiveTorchsNumber]->PadControl(&mc_devices);
}

void Player::KeyMove() {
	if (mc_devices.muptr_keyboard->GetState().IsKeyDown( DirectX::Keyboard::A )) {
		muptr_character->MovePosX(-MOVE_SPEED);
	}
	if (mc_devices.muptr_keyboard->GetState().IsKeyDown( DirectX::Keyboard::D )) {
		muptr_character->MovePosX(MOVE_SPEED);
	}
}

void Player::KeyControlGameMain(kit::Engine::KitEngine* _engine) {
	KeyMove();
	if (mc_devices.muptr_keyboard->GetState().IsKeyDown(DirectX::Keyboard::T)) {
		mc_isActiveTorchsNumber = FindUsableTorch();
		ChangeMode(static_cast<char>(MODE::Torch));
	}
	mc_devices.muptr_keyboard->Reset();
}

void Player::KeyControlTorch(kit::Engine::KitEngine*) {
	mvec_torchs[mc_isActiveTorchsNumber]->KeyControl(&mc_devices);
}

void Player::Update(kit::Engine::KitEngine* _engine) {
	(this->*mfunc_updateFunc)(_engine);

}