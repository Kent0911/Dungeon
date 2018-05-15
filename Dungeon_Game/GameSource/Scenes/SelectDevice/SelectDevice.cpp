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
	if (g_player.GetInstance().GetDevicesState()->mc_gamePad.GetState(g_player.GetInstance().GetDword()).wButtons & static_cast<int>(kit::GamePad_Buttons::Up)
		|| g_player.GetInstance().GetDevicesState()->muptr_keyboard->GetState().Up || g_player.GetInstance().GetDevicesState()->muptr_keyboard->GetState().W) {
		mc_selectDevice++;
	}
	if (g_player.GetInstance().GetDevicesState()->mc_gamePad.GetState(g_player.GetInstance().GetDword()).wButtons & static_cast<int>(kit::GamePad_Buttons::Down)
		|| g_player.GetInstance().GetDevicesState()->muptr_keyboard->GetState().Down || g_player.GetInstance().GetDevicesState()->muptr_keyboard->GetState().S) {
		mc_selectDevice--;
	}


}

void SelectDevice::Update() {
	SelectDevices();
	if (0 == mc_selectDevice % 2) {
		kit::Engine::g_sceneFonts.GetInstance().MoveFont(static_cast<int>(SelectDeviceFontList::Pointer), &kit::vec2(g_windowSize.x / 2 - 250, 200));
	}
	if (1 == mc_selectDevice % 2) {
		kit::Engine::g_sceneFonts.GetInstance().MoveFont(static_cast<int>(SelectDeviceFontList::Pointer), &kit::vec2(g_windowSize.x / 2 - 250, 300));
	}
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void SelectDevice::Render() {
	kit::Engine::g_assetsManager.GetInstance().Render();
	kit::Engine::g_sceneFonts.GetInstance().DisplayFont();
}