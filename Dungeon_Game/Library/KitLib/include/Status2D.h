#pragma once

//---------------------------------------------------------------------------------------------------
//
// 2D�Q�[���𐧍삷��ۂ̊�{�p�����[�^
// TODO:���ǂ��l�[���ɂ���
//
//---------------------------------------------------------------------------------------------------

#include "Vec2.h"

namespace kit {
	class Status2D {
	protected:
		vec2 mv_position;
		vec2 mv_target_position;

		float mf_yaw;
		float mf_rad;
	
	public:
		// mv_position�������֐�
		// TIPS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline vec2 Pos() const {
			return mv_position;
		}
		// glm::vec2�^
		void Pos(const vec2 &_pos);
		// float�^
		void Pos(const float &_x, const float &_y);

		// mv_target_position�������֐�
		// TIPS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline vec2 TargetPos() const {
			return mv_target_position;
		}
		// glm::vec2�^
		void TargetPos(const vec2 &_pos);
		// float�^
		void TargetPos(const float &_x, const float &_y);

		// mf_yaw�������֐�
		// TIPS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline float Yaw() const {
			return mf_yaw;
		}
		void Yaw(const float &_yaw);
	};
}
