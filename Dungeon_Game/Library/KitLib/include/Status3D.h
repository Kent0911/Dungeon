#pragma once

//---------------------------------------------------------------------------------------------------
//
// 3Dゲームを制作する際の基本パラメータ
// TODO:より良いネームにする
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
		// mv_positonを扱う関数
		// TPIS:引数が…無い->Get関数
		//				有る->Set関数
		inline vec3 Pos() const {
			return mv_position;
		}
		// glm::vec3型
		void Pos(const vec3 &_pos);
		// float型
		void Pos(const float &_x, const float &_y, const float &_z);


		// mv_target_positionを扱う関数
		// TIPS:引数が…無い->Get関数
		//				有る->Set関数
		inline vec3 TargetPos() const {
			return mv_position;
		}
		// glm::vec3型
		void TargetPos(const vec3 &_pos);
		// float型
		void TargetPos(const float &_x, const float &_y, const float &_z);


		// mv_upper_vectorを扱う関数
		// TIPS:引数が…無い->Get関数
		//				有る->Set関数
		inline vec3 UpperVec() const {
			return mv_upper_vector;
		}
		// glm::vec3型
		void UpperVec(const vec3 &_vec);
		// float型
		void UpperVec(const float &_x, const float &_y, const float &_z);


		// ma_yawを扱う関数
		// TIPS:引数が…無い->Get関数
		//				有る->Set関数
		inline axis Yaw() const {
			return ma_yaw;
		}
		// axis型
		void Yaw(const axis &_yaw);
		// float型
		void Yaw(const float &_vertical, const float &_horizontal);
	};
}