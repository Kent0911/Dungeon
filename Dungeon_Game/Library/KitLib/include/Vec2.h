#pragma once

//---------------------------------------------------------------------------------------------------
//
// 2次元ベクトルclassの自作
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"
#include <math.h>

#define _OX_EPSILON_ 0.000001f //誤差

namespace kit {
	// x,y要素を持つクラス
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

		// ベクトルの内積
		float Dot(const float2 &_float2) const;
		// ベクトルの外積
		float Cross(const float2 &_float2) const;
		// 長さを取得
		float Length() const;
		float LengthSq() const;
		void Normalize();
		float2 GetNorm() const;
	};
	

	// 2次元ベクトルを設定するクラス
	class vec2 :public float2 {
	public:
		vec2();
		vec2(const float &_x, const float &_y);
		vec2(const float2 &_float2);
		~vec2();

		vec2& operator= (const float2 &_float2);

		// 標準化
		void Normalize();

		// 垂直関係にあるかの判定
		bool IsVertical(const vec2 &_vec) const;

		// 平行関係にあるかの判定
		bool IsParallel(const vec2 &_vec) const;

		// 鋭角関係にあるかの判定
		bool IsSharpAngle(const vec2 &_vec) const;
	};
}