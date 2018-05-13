#pragma once

namespace kit {

//-----------------------------------------------------------------------------------------------------
//
// 3D�Q�[���ɂ����鎲�̐ݒ�
//
//-----------------------------------------------------------------------------------------------------
	class axis {
	public:
		// vertecal = y��, horizontal = z��
		float vertical, horizontal;

		axis();
		axis(const float &_vertical, const float &_horizontal);
		~axis();

		// axis�^���m�̌v�Z���s����悤�ɂ���
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

