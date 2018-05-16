#include "SelectDevice.h"

SelectDevice::SelectDevice() {
	mc_sceneNumber = static_cast<char>(SCENE::SelectDevice);
	g_player.GetInstance().SetSceneNumber(mc_sceneNumber);
	kit::Engine::g_sceneFonts.GetInstance().AddFontList(selectDeviceFont, static_cast<int>(SelectDeviceFontList::Max));
	mc_selectDevice = 0;
}

SelectDevice::~SelectDevice() {

} 

void SelectDevice::SelectDevices() {
	XINPUT_GAMEPAD padState = g_player.GetInstance().GetDevicesState()->mc_gamePad.GetState(g_player.GetInstance().GetDword());
	DirectX::Keyboard::State keyState = g_player.GetInstance().GetDevicesState()->muptr_keyboard->GetState();

	if ( padState.wButtons & static_cast<int>( kit::GamePad_Buttons::Up )|| keyState.IsKeyDown( DirectX::Keyboard::Up ) || keyState.IsKeyDown( DirectX::Keyboard::W )) {
		mc_selectDevice++;
	}
	if( keyState.IsKeyDown( DirectX::Keyboard::Down ) || keyState.IsKeyDown( DirectX::Keyboard::S ) ){
		mc_selectDevice--;
	}
	if (padState.wButtons & static_cast<int>(kit::GamePad_Buttons::A) || keyState.IsKeyDown( DirectX::Keyboard::Enter )) {
		if (0 == mc_selectDevice % 2) {
			g_player.GetInstance().SetDevice(true);
		}
		else {
			g_player.GetInstance().SetDevice(false);
		}
	}
	g_player.GetInstance().GetDevicesState()->muptr_keyboard->Reset();
}

void SelectDevice::Update() {
	SelectDevices();
	if (0 == abs( mc_selectDevice ) % 2) {
		kit::Engine::g_sceneFonts.GetInstance().MoveFont(static_cast<int>(SelectDeviceFontList::Pointer), &kit::vec2(g_windowSize.x / 2 - 250, 200));
	}
	if (1 == abs( mc_selectDevice ) % 2) {
		kit::Engine::g_sceneFonts.GetInstance().MoveFont(static_cast<int>(SelectDeviceFontList::Pointer), &kit::vec2(g_windowSize.x / 2 - 250, 300));
	}
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void SelectDevice::Render() {
	kit::Engine::g_assetsManager.GetInstance().Render();
	kit::Engine::g_sceneFonts.GetInstance().DisplayFont();
}