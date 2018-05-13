#pragma once

//---------------------------------------------------------------------------------------------------
//
// 3�����x�N�g��class�̎���
//
//---------------------------------------------------------------------------------------------------
#include "Defines.h"
#include <math.h>

#define _OX_EPSILON_ 0.000001f

namespace kit {
	// x,y,z�̗v�f�����N���X
	class float3 {
	public:
		float x, y, z;

		float3();
		float3(const float &_x, const float &_y, const float &_z);
		~float3();

		float3 operator+ (const float3 &_float3) const;
		float3 operator+= (const float3 &_float3);
		float3 operator- (const float3 &_float3) const;
		float3 operator- () const;
		float3 operator-= (const float3 &_float3);
		float3 operator* (const float &_value) const;
		float3 operator*= (const float &_value);
		float3 operator/ (const float &_value) const;
		float3 operator/= (const float &_value);
		float3 operator* (const float3 &_float3) const;
		float3 operator*= (const float3 &_float3);
		float3 operator/ (const float3 &_float3) const;
		float3 operator/= (const float3 &_float3);

		friend float3 operator* (const float &_value, const float3 &_float3) {
			return float3(_float3.x * _value, _float3.y * _value, _float3.z * _value);
		}
		friend float3 operator/ (const float &_value, const float3 &_float3) {
			return float3(_float3.x / _value, _float3.y / _value, _float3.z / _value);
		}

		// �x�N�g���̓���
		float Dot(const float3 &_float3) const;
		// �x�N�g���̊O��
		float3 Cross(const float3 &_float3) const;
		// �������擾
		float Length() const;
		float LengthSq() const;

		void Normalize();
		float3 GetNorm() const;
	};


	// 3D�x�N�g��
	class vec3 :public float3 {
	public:
		vec3();
		vec3(const float &_x, const float &_y, const float &_z);
		vec3(const float3 &_float3);
		~vec3();

		vec3& operator= (const float3 &_float3);

		// �W����
		void Normalize();

		// �����֌W�ɂ��邩�̔���
		bool IsVertical(const vec3 &_vec) const;

		// ���s�֌W�ɂ��邩�̔���
		bool IsParallel(const vec3 &_vec) const;

		// �s�p�֌W�ɂ��邩�̔���
		bool IsSharpAngle(const vec3 &_vec) const;
	};
}