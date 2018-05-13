#pragma once

#include <memory>

#include "../../../KitEngine/KitBehaviour/KitBehaviour.h"
#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"
#include "../../Player/Player.h"

extern class Player g_player;
extern class Devices;

class Torch :public kit::Engine::KitBehaviour {
private:
	bool						mb_isUsed;
	kit::Circle2D				mc_circle;
	ID3D11ShaderResourceView*	mpd3d_texture;

public:
	Torch();
	~Torch();
	inline bool IsUsed() const {
		return mb_isUsed;
	}
	inline const void SetPos(const kit::vec3* _pos) {
		mvec_position = *_pos;
	}

	void GPMoveTorch(Devices* _device);
	void GPControl(Devices* _device);

	void KeyMoveTorch(Devices* _device);
	void KeyControl(Devices* _device);
	void TurnOnLight();

	virtual void Update();
	virtual void Render();
};