#pragma once

#include <d3d11.h>
#include <memory>

#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../KitEngine/KitEngine.h"
#include "../../../KitEngine/KitBehaviour/KitBehaviour.h"
#include "../../../Library/DirectXTK/include/DDSTextureLoader.h"
#include "../../../Library/DirectXTK/include/WICTextureLoader.h"
#include "../../../Library/DirectXTK/include/SimpleMath.h"
#include "../../../Library/DirectXTK/include/SpriteBatch.h"
#include "../../../KitEngine/Render/Render.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"

class Character:public kit::Engine::KitBehaviour{
private:
	std::unique_ptr<ID3D11ShaderResourceView>		muptr_pd3dTexture;
	bool											mb_isAnimated;
	
public:
	Character();
	~Character();

	HRESULT LoadFile();

	inline kit::vec3 GetPos() const {
		return mvec_position;
	}
	inline void MovePosX(const short _x) {
		mvec_position.x += (float)_x;
	}
	inline void MovePosY(const short _y) {
		mvec_position.y += (float)_y;
	}
	inline void Animation(bool _flag) {
		mb_isAnimated = _flag;
	}
	inline bool Animation() const {
		return mb_isAnimated;
	}

	virtual void Update();
	virtual void Render();
};
