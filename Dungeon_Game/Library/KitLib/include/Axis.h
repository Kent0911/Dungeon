#pragma once

namespace kit {

//-----------------------------------------------------------------------------------------------------
//
// 3DÉQÅ[ÉÄÇ…Ç®ÇØÇÈé≤ÇÃê›íË
//
//-----------------------------------------------------------------------------------------------------
	class axis {
	public:
		// vertecal = yé≤, horizontal = zé≤
		float vertical, horizontal;

		axis();
		axis(const float &_vertical, const float &_horizontal);
		~axis();

		// axiså^ìØémÇÃåvéZÇçsÇ¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
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

