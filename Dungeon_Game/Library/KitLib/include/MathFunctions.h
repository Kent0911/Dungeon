#pragma once

//---------------------------------------------------------------------------------------------------
//
// �p�o����Z�p�֐��͑S�Ă����ɒ�`����
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <math.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Axis.h"

namespace kit {
	// ���Z��
	template <class T>
	T Addition(const T &_value1, const T &_value2) {
		return _value1 + _value2;
	}

	// ���Z��
	template <class T>
	T Subtraction(const T &_sub, const T &_value) {
		return _sub - _value;
	}

	// ��Z��
	template <class T>
	T Multiplication(const T &_value1, const T &_value2) {
		return _value1 * _value2;
	}

	// ���Z��
	template <class T>
	T Division(const T &_div, const T &_value) {
		return _div / _value;
	}

	// yaw��rad�Ɍv�Z��������
	// float�^
	float CalculateRadian(const float &_yaw);
	// axis�^
	axis CalculateRadian(const axis &_yaw);

	// Object���m�̋������v�Z���鎮
	// vec2�^
	float DistanceObjects(const vec2 &_mypos, const vec2 &_targetpos);
	// vec3�^
	float DistanceObjects(const vec3 &_mypos, const vec3 &_targetpos);

	// 2D�̓���
	// float2�N���X�ɂ���`����Ă��邽�߁A������𗘗p���Ă���ꍇ�͎g��Ȃ�����
	template <class T>
	T& DotProduct(const T &_x1, const T &_y1, const T &_x2, const T &_y2) {
		return _x1 * _x2 + _y1 * _y2;
	}

	// 3D�̓���
	// float3�N���X�ɂ���`����Ă��邽�߁A������𗘗p���Ă���ꍇ�͎g��Ȃ�����
	template <class T>
	T& DotProduct(const T &_x1, const T &_y1, const T &_z1, const T &_x2, const T &_y2, const T &_z2) {
		return _x1 * _x2 + _y1 * y2 + _z1 * _z2;
	}


	// Target������֌�����ύX����v�Z��
	// ������float�^
	// TPIS:�߂�l��Radian
	float ChaseDirection(const float & _mypos_x, const float &_mypos_y, const float &_targetpos_x, const float &_targetpos_y);
	// ������glm::vec2�^
	// TPIS:�߂�l��Radian
	float ChaseDirection(const vec2 &_mypos, const vec2 &_targetpos);


	// ���ʂ�Object��ǂ�������v�Z��
	// glm::vec2�^ ������float�^
	vec2 ChaseObject2D(const float &_mypos_x, const float &_mypos_y, const float &_targetpos_x, const float &_targetpos_y, const float &_chasespeed);
	// glm::vec2�^ ������glm::vec2�^
	vec2 ChaseObject2D(const vec2 &_mypos, const vec2 &_targetpos, const float &_chasespeed);
	// glm::vec3�^
	vec3 ChaseObject2D(const vec3 &_mypos, const vec3 &_targetpos, const float &_chasespeed);
	// glm::vec3�^ openGL�p�iopenGL��x,z���ʂȂ̂Łj
	vec3 glChaseObject2D(const vec3 &_mypos, const vec3 &_targetpos, const float &_chasesepeed);

}