#pragma once

#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>

#include "../../../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../../../Configurations/GameConfiguration/GameConfiguration.h"
#include "../../../../KitEngine/Render/Render.h"
#include "../../../../Library/DirectXTK/include/WICTextureLoader.h"
#include "../../../../Library/DirectXTK/include/SimpleMath.h"

enum class RGBA{
	r,
	g,
	b,
	a,
	Max
};

class Filter {
private:
	std::unique_ptr<ID3D11ShaderResourceView>	muptr_pd3dTexture;
	DirectX::XMVECTOR							mx_color;
	int											mi_appeardTime;

	void Initialize();
public:
	HRESULT	LoadFile();
	bool Filtering();
	void Render();
};
