#pragma once

//---------------------------------------------------------------------------------------------------
//
// 2�����x�N�g��class�̎���
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"
#include <math.h>

#define _OX_EPSILON_ 0.000001f //�덷

namespace kit {
	// x,y�v�f�����N���X
	class float2 {
	public:
		float x, y;

		float2();
		float2(const float &_x,const float &_y);
		~float2();

		float2 operator= (const float2 &_float2);
		float2 operator+ (const float2 &_float2) const;
		float2 operator+= (const float2 &_float2);
		float2 operator- () const;
		float2 operator- (const float2 &_float2) const;
		float2 operator-= (const float2 &_float2);
		float2 operator* (const float &_value) const;
		float2 operator*= (const float &_value);
		float2 operator/ (const float &_value) const;
		float2 operator/= (const float &_value);
		float2 operator* (const float2 &_float2) const;
		float2 operator*= (const float2 &_float2);
		float2 operator/ (const float2 &_float2) const;
		float2 operator/= (const float2 &_float2);

		friend float2 operator* (const float &_value, const float2 &_float2) {
			return float2(_float2.x * _value, _float2.y * _value);
		}
		friend float2 operator/ (const float &_value, const float2 &_float2) {
			return float2(_float2.x / _value, _float2.y / _value);
		}

		// �x�N�g���̓���
		float Dot(const float2 &_float2) const;
		// �x�N�g���̊O��
		float Cross(const float2 &_float2) const;
		// �������擾
		float Length() const;
		float LengthSq() const;
		void Normalize();
		float2 GetNorm() const;
	};
	

	// 2�����x�N�g����ݒ肷��N���X
	class vec2 :public float2 {
	public:
		vec2();
		vec2(const float &_x, const float &_y);
		vec2(const float2 &_float2);
		~vec2();

		vec2& operator= (const float2 &_float2);

		// �W����
		void Normalize();

		// �����֌W�ɂ��邩�̔���
		bool IsVertical(const vec2 &_vec) const;

		// ���s�֌W�ɂ��邩�̔���
		bool IsParallel(const vec2 &_vec) const;

		// �s�p�֌W�ɂ��邩�̔���
		bool IsSharpAngle(const vec2 &_vec) const;
	};
}