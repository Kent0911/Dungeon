#include "Torch.h"

Torch::Torch() {
	mb_isUsed = false;
}

Torch::~Torch() {

}

void Torch::GPMoveTorch(Devices* _device) {
	short thumbLX = _device->mc_gamePad.GetState(g_player.GetInstance().GetDword()).sThumbLX;
	short thumbLY = _device->mc_gamePad.GetState(g_player.GetInstance().GetDword()).sThumbLY;
	if (thumbLX > GAMEPAD_THRESHOLD | -GAMEPAD_THRESHOLD > thumbLX) {
		mvec_position.x += thumbLX;
	}
	if (thumbLY > GAMEPAD_THRESHOLD | -GAMEPAD_THRESHOLD > thumbLY) {
		mvec_position.y += thumbLY;
	}
}

void Torch::GPControl(Devices* _device) {
	GPMoveTorch(_device);

	// GamePad = Åõ
	if (static_cast<unsigned int>(kit::GamePad_Buttons::A) & _device->mc_gamePad.GetState(g_player.GetInstance().GetDword()).wButtons) {
		TurnOnLight();
		mb_isUsed = true;
		g_player.GetInstance().SubTorchsCounts();
		g_player.GetInstance().SetModeFlag(static_cast<char>(MODE::Player));
	}
	
	// GamePad = Å~
	if (static_cast<unsigned int>(kit::GamePad_Buttons::B) & _device->mc_gamePad.GetState(g_player.GetInstance().GetDword()).wButtons) {
		g_player.GetInstance().SetModeFlag(static_cast<char>(MODE::Player));
	}

}

void Torch::KeyMoveTorch(Devices* _device) {
	kit::vec2 mousePos = { (float)_device->muptr_mouse->GetState().x, (float)_device->muptr_mouse->GetState().y };
	mvec_position.x = mousePos.x;
	mvec_position.y = mousePos.y;
}

void Torch::KeyControl(Devices* _device) {
	KeyMoveTorch(_device);
	
	//Keyboard Enter key or Mouse left click
	if (_device->muptr_keyboard->GetState().Enter || _device->muptr_mouse->GetState().leftButton) {
		TurnOnLight();
		mb_isUsed = true;
		g_player.GetInstance().SubTorchsCounts();
		g_player.GetInstance().SetModeFlag(static_cast<char>(MODE::Player));
	}

	// Keyboard T key or Mouse right click
	if (_device->muptr_keyboard->GetState().T || _device->muptr_mouse->GetState().rightButton) {
		g_player.GetInstance().SetModeFlag(static_cast<char>(MODE::Player));
	}
}

void Torch::TurnOnLight() {

}

void Torch::Update() {
	mc_circle.mp_center = CastVec2Pos(&mvec_position);
}

void Torch::Render() {
	
}