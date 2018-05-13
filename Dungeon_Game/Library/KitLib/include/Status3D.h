#pragma once

//---------------------------------------------------------------------------------------------------
//
// 3D�Q�[���𐧍삷��ۂ̊�{�p�����[�^
// TODO:���ǂ��l�[���ɂ���
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <math.h>

#include "Vec3.h"
#include "Axis.h"

namespace kit {
	class Status3D {
	protected:
		vec3 mv_position;
		vec3 mv_target_position;
		vec3 mv_upper_vector;
		axis ma_yaw;
		axis ma_rad;

	public:
		// mv_positon�������֐�
		// TPIS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline vec3 Pos() const {
			return mv_position;
		}
		// glm::vec3�^
		void Pos(const vec3 &_pos);
		// float�^
		void Pos(const float &_x, const float &_y, const float &_z);


		// mv_target_position�������֐�
		// TIPS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline vec3 TargetPos() const {
			return mv_position;
		}
		// glm::vec3�^
		void TargetPos(const vec3 &_pos);
		// float�^
		void TargetPos(const float &_x, const float &_y, const float &_z);


		// mv_upper_vector�������֐�
		// TIPS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline vec3 UpperVec() const {
			return mv_upper_vector;
		}
		// glm::vec3�^
		void UpperVec(const vec3 &_vec);
		// float�^
		void UpperVec(const float &_x, const float &_y, const float &_z);


		// ma_yaw�������֐�
		// TIPS:�������c����->Get�֐�
		//				�L��->Set�֐�
		inline axis Yaw() const {
			return ma_yaw;
		}
		// axis�^
		void Yaw(const axis &_yaw);
		// float�^
		void Yaw(const float &_vertical, const float &_horizontal);
	};
}