#include "Filter.h"

void Filter::Initialize() {
	mx_color = {};
	mi_appeardTime = 0;
}

HRESULT Filter::LoadFile() {
	HRESULT hr = S_OK;
	Initialize();
	ID3D11ShaderResourceView* resource;
	hr = DirectX::CreateWICTextureFromFile(kit::Engine::g_pd3dDevice, L"Resource/Stage/Filter.png", nullptr, &resource);
	if (FAILED(hr)) { return hr; }
	muptr_pd3dTexture.reset(resource);
}

bool Filter::Filtering() {
	if (FILTER_APPEARD_TIME == mi_appeardTime) {
		return true;
	}
	else {
		float alpha = 1.f / FILTER_APPEARD_TIME;
		mx_color.m128_f32[static_cast<char>(RGBA::a)] += alpha;
		mi_appeardTime++;
		return false;
	}
}

void Filter::Render() {
	kit::Engine::g_uptrSprites->Draw(muptr_pd3dTexture.get(), DirectX::XMFLOAT2(0, 0),nullptr, mx_color);
}