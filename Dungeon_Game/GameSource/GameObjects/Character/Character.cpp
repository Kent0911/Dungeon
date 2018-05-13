#include "Character.h"

Character::Character() {
	LoadFile();
}

Character::~Character() {

}


// TODO キャラクターの画像を貰ったらファイルネームを変える事
HRESULT Character::LoadFile() {
	HRESULT hr = S_OK;
	hr = DirectX::CreateDDSTextureFromFile(kit::Engine::g_pd3dDevice, L"filename", nullptr, &mpd3d_texture);
	if (FAILED(hr)) { return hr; }
}

void Character::Update() {

}

void Character::Render() {
	kit::Engine::g_uptrSprites->Draw(mpd3d_texture, DirectX::XMFLOAT2(mvec_position.x, mvec_position.y), nullptr, DirectX::Colors::White);
}