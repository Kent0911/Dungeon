#pragma once

//---------------------------------------------------------------------------------------------------
//
// Random class の定義
// WARNING:Singleton化しているため、複数のinstanceを保持できない
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <random>

#include "Singleton.h"

namespace kit {
	class Random :public Singleton<Random> {
	private:
		friend class Singleton<Random>;
		std::mt19937 m_mt;
		std::random_device m_rand_device;

		Random();
	public:
		// _min〜_maxの範囲でrandomにfloat型の値を返す
		template <class T>
		float GetRand(const T &_min, const T &_max) const;
	};
}
