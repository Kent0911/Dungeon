#pragma once

//---------------------------------------------------------------------------------------------------
//
// 3次元ベクトルclassの自作
//
//---------------------------------------------------------------------------------------------------
#include "Defines.h"
#include <math.h>

#define _OX_EPSILON_ 0.000001f

namespace kit {
	// x,y,zの要素を持つクラス
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

		// ベクトルの内積
		float Dot(const float3 &_float3) const;
		// ベクトルの外積
		float3 Cross(const float3 &_float3) const;
		// 長さを取得
		float Length() const;
		float LengthSq() const;

		void Normalize();
		float3 GetNorm() const;
	};


	// 3Dベクトル
	class vec3 :public float3 {
	public:
		vec3();
		vec3(const float &_x, const float &_y, const float &_z);
		vec3(const float3 &_float3);
		~vec3();

		vec3& operator= (const float3 &_float3);

		// 標準化
		void Normalize();

		// 垂直関係にあるかの判定
		bool IsVertical(const vec3 &_vec) const;

		// 平行関係にあるかの判定
		bool IsParallel(const vec3 &_vec) const;

		// 鋭角関係にあるかの判定
		bool IsSharpAngle(const vec3 &_vec) const;
	};
}