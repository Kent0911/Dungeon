#pragma once

#include <d3d11.h>
#include <memory>

#include "../../../KitEngine/KitBehaviour/KitBehaviour.h"
#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../KitEngine/KitEngine.h"
#include "../../../Library/DirectXTK/include/DDSTextureLoader.h"
#include "../../../Library/DirectXTK/include/SimpleMath.h"
#include "../../../Library/DirectXTK/include/SpriteBatch.h"
#include "../../../KitEngine/Render/Render.h"

class Character :public kit::Engine::KitBehaviour {
private:
	ID3D11ShaderResourceView*	mpd3d_texture;
	
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

	virtual void Update();
	virtual void Render();
};
