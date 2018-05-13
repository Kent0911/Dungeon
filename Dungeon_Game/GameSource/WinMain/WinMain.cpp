#include <d3d11.h>
#include <memory>

#include "../../KitEngine/KitEngine.h"
#include "../Player/Player.h"
#include "../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../Configurations/GameConfiguration/GameConfiguration.h"
#include "../Scenes/Title/Title.h"

// externの警告の非表示
#pragma warning (disable:4091)

//--------------------------------------------------------------------------------------------------------------------------------------------
//
// ゲームで使用するグローバル変数
//
//--------------------------------------------------------------------------------------------------------------------------------------------
extern Player g_player;

//--------------------------------------------------------------------------------------------------------------------------------------------
//
// セットアップ関数
//
//--------------------------------------------------------------------------------------------------------------------------------------------
kit::Engine::Config SetUp() {
	kit::Engine::Config config;
	config.mlp_str = (LPSTR)GAME_TITLE;
	config.mc_frameRate.Numerator(static_cast<UINT>(FRAME_RATE::Numerator));
	config.mv_windowSize = g_windowSize;
	config.msptr_startScene = START_SCENE;
	return config;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//
// WinMain関数
//
//--------------------------------------------------------------------------------------------------------------------------------------------

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	kit::Engine::KitEngine* p_kitEngine = new kit::Engine::KitEngine(hInstance, nCmdShow, &SetUp());

	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			g_player.GetInstance().Update(p_kitEngine);
			p_kitEngine->Update();
			p_kitEngine->Render();
		}
	}

	delete p_kitEngine;

	return (int)msg.wParam;
}