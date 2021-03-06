#pragma once

//---------------------------------------------------------------------------------------------------
//
// 頻出する算術関数は全てここに定義する
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <math.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Axis.h"

namespace kit {
	// 加算式
	template <class T>
	T Addition(const T &_value1, const T &_value2) {
		return _value1 + _value2;
	}

	// 減算式
	template <class T>
	T Subtraction(const T &_sub, const T &_value) {
		return _sub - _value;
	}

	// 乗算式
	template <class T>
	T Multiplication(const T &_value1, const T &_value2) {
		return _value1 * _value2;
	}

	// 除算式
	template <class T>
	T Division(const T &_div, const T &_value) {
		return _div / _value;
	}

	// yawをradに計算し直す式
	// float型
	float CalculateRadian(const float &_yaw);
	// axis型
	axis CalculateRadian(const axis &_yaw);

	// Object同士の距離を計算する式
	// vec2型
	float DistanceObjects(const vec2 &_mypos, const vec2 &_targetpos);
	// vec3型
	float DistanceObjects(const vec3 &_mypos, const vec3 &_targetpos);

	// 2Dの内積
	// float2クラスにも定義されているため、そちらを利用している場合は使わないこと
	template <class T>
	T& DotProduct(const T &_x1, const T &_y1, const T &_x2, const T &_y2) {
		return _x1 * _x2 + _y1 * _y2;
	}

	// 3Dの内積
	// float3クラスにも定義されているため、そちらを利用している場合は使わないこと
	template <class T>
	T& DotProduct(const T &_x1, const T &_y1, const T &_z1, const T &_x2, const T &_y2, const T &_z2) {
		return _x1 * _x2 + _y1 * y2 + _z1 * _z2;
	}


	// Targetを方向へ向きを変更する計算式
	// 引数がfloat型
	// TPIS:戻り値はRadian
	float ChaseDirection(const float & _mypos_x, const float &_mypos_y, const float &_targetpos_x, const float &_targetpos_y);
	// 引数がglm::vec2型
	// TPIS:戻り値はRadian
	float ChaseDirection(const vec2 &_mypos, const vec2 &_targetpos);


	// 平面でObjectを追いかける計算式
	// glm::vec2型 引数がfloat型
	vec2 ChaseObject2D(const float &_mypos_x, const float &_mypos_y, const float &_targetpos_x, const float &_targetpos_y, const float &_chasespeed);
	// glm::vec2型 引数がglm::vec2型
	vec2 ChaseObject2D(const vec2 &_mypos, const vec2 &_targetpos, const float &_chasespeed);
	// glm::vec3型
	vec3 ChaseObject2D(const vec3 &_mypos, const vec3 &_targetpos, const float &_chasespeed);
	// glm::vec3型 openGL用（openGLはx,z平面なので）
	vec3 glChaseObject2D(const vec3 &_mypos, const vec3 &_targetpos, const float &_chasesepeed);

}