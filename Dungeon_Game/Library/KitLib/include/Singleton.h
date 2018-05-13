#pragma once
//---------------------------------------------------------------------------------------------------
//
// Singleton class�̊�N���X
// TPIS:���̃N���X���p�����邱�Ƃ�Singleton�����邱�Ƃ��ł���
//
//---------------------------------------------------------------------------------------------------
#include <memory>

namespace kit {
	template <class T>
	class Singleton {
	private:
		typedef std::unique_ptr<T> singleton_pointer_type;
		inline static T *CreateInstance() {
			return new T();
		}
		inline static T &GetReference(const singleton_pointer_type &_ptr) {
			return *_ptr;
		}
	protected:
		Singleton() {}

	public:
		static T& GetInstance() {
			static typename T::singleton_pointer_type s_singleton(T::CreateInstance());
			return GetReference(s_singleton);
		}

	private:
		Singleton(const Singleton &) = delete;
		Singleton& operator=(const Singleton &) = delete;
		Singleton(Singleton &&) = delete;
		Singleton& operator=(Singleton &&) = delete;
	};
}
