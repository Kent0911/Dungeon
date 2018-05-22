#pragma once

#include <d3d11.h>

#include "../../../KitEngine/KitBehaviour/KitBehaviour.h"
#include "../../../KitEngine/Render/Render.h"
#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../Configurations/SystemConfiguration/SystemConfiguration.h"

class Camera{
private:
	kit::Engine::CameraStatus	mc_state;

	void(Camera::*mfunc_CameraFunc)();
	void Tutorial();
	void GameMain();

public:
	Camera();
	~Camera();

	inline void SetPosition(kit::vec3* _pos) {
		mc_state.mvec_position = *_pos;
	}
	inline void MovePosition(kit::vec3* _movePos, int _count);

	void Update();

};