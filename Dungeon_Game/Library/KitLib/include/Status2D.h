#pragma once

//---------------------------------------------------------------------------------------------------
//
// 2Dゲームを制作する際の基本パラメータ
// TODO:より良いネームにする
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
		// mv_positionを扱う関数
		// TIPS:引数が…無い->Get関数
		//				有る->Set関数
		inline vec2 Pos() const {
			return mv_position;
		}
		// glm::vec2型
		void Pos(const vec2 &_pos);
		// float型
		void Pos(const float &_x, const float &_y);

		// mv_target_positionを扱う関数
		// TIPS:引数が…無い->Get関数
		//				有る->Set関数
		inline vec2 TargetPos() const {
			return mv_target_position;
		}
		// glm::vec2型
		void TargetPos(const vec2 &_pos);
		// float型
		void TargetPos(const float &_x, const float &_y);

		// mf_yawを扱う関数
		// TIPS:引数が…無い->Get関数
		//				有る->Set関数
		inline float Yaw() const {
			return mf_yaw;
		}
		void Yaw(const float &_yaw);
	};
}
