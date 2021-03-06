#pragma once

namespace kit {

//-----------------------------------------------------------------------------------------------------
//
// 3Dゲームにおける軸の設定
//
//-----------------------------------------------------------------------------------------------------
	class axis {
	public:
		// vertecal = y軸, horizontal = z軸
		float vertical, horizontal;

		axis();
		axis(const float &_vertical, const float &_horizontal);
		~axis();

		// axis型同士の計算を行えるようにする
		axis operator= (const axis &_axis);
		axis operator+ (const axis &_axis) const;
		axis operator+= (const axis &_axis);
		axis operator- (const axis &_axis) const;
		axis operator-= (const axis &_axis);
		axis operator* (const float &_value) const;
		axis operator*= (const float &_value);
		axis operator/ (const float &_value) const;
		axis operator/= (const float &_value);
		axis operator* (const axis &_axis) const;
		axis operator*= (const axis &_axis);
		axis operator/ (const axis &_axis) const;
		axis operator/= (const axis &_axis);
	};
}

