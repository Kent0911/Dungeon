#include "Tutorial.h"

Tutorial::Tutorial() {
	mc_sceneNumber = static_cast<char>(SCENE::Tutorial);
	g_player.GetInstance().SceneNumber(mc_sceneNumber);
	LoadFile();
}

Tutorial::~Tutorial() {

}

HRESULT Tutorial::LoadFile() {
	HRESULT hr = S_OK;
	ID3D11ShaderResourceView* resource;
	hr = DirectX::CreateWICTextureFromFile(kit::Engine::g_pd3dDevice, L"Resource/Stage/Filter.bmp", nullptr, &resource);
	if (FAILED(hr)) { return hr; }
	muptr_pd3dTexture.reset(resource);
}

void Tutorial::Update() {
	kit::Engine::g_assetsManager.GetInstance().Update();
}

void Tutorial::Render() {
	kit::Engine::g_uptrSprites->Draw(muptr_pd3dTexture.get(), DirectX::XMFLOAT2(0, 0), nullptr, DirectX::Colors::White);
	kit::Engine::g_assetsManager.GetInstance().Render();
}