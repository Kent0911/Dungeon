#include "Character.h"

Character::Character() {
	LoadFile();
	mb_isAnimated = false;
}

Character::~Character() {
	muptr_pd3dTexture.release();
}


// TODO キャラクターの画像を貰ったらファイルネームを変える事
HRESULT Character::LoadFile() {
	HRESULT hr = S_OK;
	ID3D11ShaderResourceView* resource;
	hr = DirectX::CreateWICTextureFromFile(kit::Engine::g_pd3dDevice, L"Resource/Character/Character.jpg", nullptr,&resource, static_cast<UINT>(TEXTURE::Character));
	if (FAILED(hr)) { return hr; }
	muptr_pd3dTexture.reset(resource);
}


void Character::Update() {

}

void Character::Render() {
	kit::vec2 displayPos = { mvec_position.x ,g_windowSize.y - mvec_position.y - static_cast<UINT>(TEXTURE::Character) };
	kit::Engine::g_uptrSprites->Draw(muptr_pd3dTexture.get(), DirectX::XMFLOAT2(displayPos.x, displayPos.y), nullptr, DirectX::Colors::White);
}