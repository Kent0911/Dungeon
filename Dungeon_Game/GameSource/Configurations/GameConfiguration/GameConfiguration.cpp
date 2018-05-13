#include "GameConfiguration.h"

kit::vec2 CastVec2Pos(kit::vec3* _pos) {
	kit::vec2 pos;
	pos.x = _pos->x;
	pos.y = _pos->y;
	return pos;
}
