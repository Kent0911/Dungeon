#pragma once

#include "../../../KitEngine/KitBehaviour/KitBehaviour.h"
#include "../../../Library/KitLib/include/Kitlib.h"

class LeadingInsect :public kit::Engine::KitBehaviour {
private:
	bool mb_isUsed;
	kit::Circle2D mc_circle;

public:
	LeadingInsect();
	inline bool IsUsed() const {
		return mb_isUsed;
	}
	inline void IsUsed(const bool _flag) {
		mb_isUsed = _flag;
	}

	virtual void Update();
	virtual void Render();
};