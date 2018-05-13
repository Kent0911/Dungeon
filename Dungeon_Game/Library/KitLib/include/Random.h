#pragma once

//---------------------------------------------------------------------------------------------------
//
// Random class ‚Ì’è‹`
// WARNING:Singleton‰»‚µ‚Ä‚¢‚é‚½‚ßA•¡”‚Ìinstance‚ğ•Û‚Å‚«‚È‚¢
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
		// _min`_max‚Ì”ÍˆÍ‚Årandom‚ÉfloatŒ^‚Ì’l‚ğ•Ô‚·
		template <class T>
		float GetRand(const T &_min, const T &_max) const;
	};
}
