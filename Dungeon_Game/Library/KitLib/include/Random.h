#pragma once

//---------------------------------------------------------------------------------------------------
//
// Random class �̒�`
// WARNING:Singleton�����Ă��邽�߁A������instance��ێ��ł��Ȃ�
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
		// _min�`_max�͈̔͂�random��float�^�̒l��Ԃ�
		template <class T>
		float GetRand(const T &_min, const T &_max) const;
	};
}
