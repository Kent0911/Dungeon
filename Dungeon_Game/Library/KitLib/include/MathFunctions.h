#pragma once

//---------------------------------------------------------------------------------------------------
//
// •po‚·‚éZpŠÖ”‚Í‘S‚Ä‚±‚±‚É’è‹`‚·‚é
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <math.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Axis.h"

namespace kit {
	// ‰ÁZ®
	template <class T>
	T Addition(const T &_value1, const T &_value2) {
		return _value1 + _value2;
	}

	// Œ¸Z®
	template <class T>
	T Subtraction(const T &_sub, const T &_value) {
		return _sub - _value;
	}

	// æZ®
	template <class T>
	T Multiplication(const T &_value1, const T &_value2) {
		return _value1 * _value2;
	}

	// œZ®
	template <class T>
	T Division(const T &_div, const T &_value) {
		return _div / _value;
	}

	// yaw‚ğrad‚ÉŒvZ‚µ’¼‚·®
	// floatŒ^
	float CalculateRadian(const float &_yaw);
	// axisŒ^
	axis CalculateRadian(const axis &_yaw);

	// Object“¯m‚Ì‹——£‚ğŒvZ‚·‚é®
	// vec2Œ^
	float DistanceObjects(const vec2 &_mypos, const vec2 &_targetpos);
	// vec3Œ^
	float DistanceObjects(const vec3 &_mypos, const vec3 &_targetpos);

	// 2D‚Ì“àÏ
	// float2ƒNƒ‰ƒX‚É‚à’è‹`‚³‚ê‚Ä‚¢‚é‚½‚ßA‚»‚¿‚ç‚ğ—˜—p‚µ‚Ä‚¢‚éê‡‚Íg‚í‚È‚¢‚±‚Æ
	template <class T>
	T& DotProduct(const T &_x1, const T &_y1, const T &_x2, const T &_y2) {
		return _x1 * _x2 + _y1 * _y2;
	}

	// 3D‚Ì“àÏ
	// float3ƒNƒ‰ƒX‚É‚à’è‹`‚³‚ê‚Ä‚¢‚é‚½‚ßA‚»‚¿‚ç‚ğ—˜—p‚µ‚Ä‚¢‚éê‡‚Íg‚í‚È‚¢‚±‚Æ
	template <class T>
	T& DotProduct(const T &_x1, const T &_y1, const T &_z1, const T &_x2, const T &_y2, const T &_z2) {
		return _x1 * _x2 + _y1 * y2 + _z1 * _z2;
	}


	// Target‚ğ•ûŒü‚ÖŒü‚«‚ğ•ÏX‚·‚éŒvZ®
	// ˆø”‚ªfloatŒ^
	// TPIS:–ß‚è’l‚ÍRadian
	float ChaseDirection(const float & _mypos_x, const float &_mypos_y, const float &_targetpos_x, const float &_targetpos_y);
	// ˆø”‚ªglm::vec2Œ^
	// TPIS:–ß‚è’l‚ÍRadian
	float ChaseDirection(const vec2 &_mypos, const vec2 &_targetpos);


	// •½–Ê‚ÅObject‚ğ’Ç‚¢‚©‚¯‚éŒvZ®
	// glm::vec2Œ^ ˆø”‚ªfloatŒ^
	vec2 ChaseObject2D(const float &_mypos_x, const float &_mypos_y, const float &_targetpos_x, const float &_targetpos_y, const float &_chasespeed);
	// glm::vec2Œ^ ˆø”‚ªglm::vec2Œ^
	vec2 ChaseObject2D(const vec2 &_mypos, const vec2 &_targetpos, const float &_chasespeed);
	// glm::vec3Œ^
	vec3 ChaseObject2D(const vec3 &_mypos, const vec3 &_targetpos, const float &_chasespeed);
	// glm::vec3Œ^ openGL—piopenGL‚Íx,z•½–Ê‚È‚Ì‚Åj
	vec3 glChaseObject2D(const vec3 &_mypos, const vec3 &_targetpos, const float &_chasesepeed);

}