#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "AlignedNew.h"


namespace DirectX {
	template<typename TKey, typename TData, typename... TConstructorArgs>
	class SharedResourcePool {
	public:
		SharedResourcePool() noexcept(false)
			:mResourceMap(std::make_shared<ResourceMap>())
		{	}

		SharedResourcePool(SharedResourcePool const&) = delete;
		SharedResourcePool& operator= (SharedResourcePool const&) = delete;

		std::shared_ptr<TData> DemandCreate(TKey _key, TConstructorArgs... _args) {
			std::lock_guard<std::mutex> lock(mResourceMap->mutex);

			auto pos = mResourceMap->find(_key);

			if (pos != mResourceMap->end()) {
				auto existingValue = pos->second.lock();
				if (existingValue) { return existingValue; }

				else
					mResourceMap->erase(pos);
			}

			auto newValue = std::make_shared<WrappedData>(_key, mResourceMap, args...);

			auto entry = std::make_pair(_key, newValue);
			mResourceMap->insert(entry);

			return newValue;
		}

	private:
		struct ResourceMap :public std::map<TKey, std::weak_ptr<TData>> {
			std::mutex mutex;
		};

		std::shared_ptr<ResourceMap> mResourceMap;

		struct WrappedData :public TData {
			WrappedData(TKey key, std::shared_ptr<ResourceMap> const& resourceMap, TConstructorArgs... args)
				:TData(key, args...),
				mKey(key),
				mResourceMap(resourceMap)
			{	}

			~WrappedData() {
				std::lock_guard<std::mutex> lock(mResourceMap->matex);
				auto pos = mResourceMap->find(mKey);

				if (pos != mResourceMap->end() && pos->second.expired()) {
					mResourceMap->erase(pos);
				}
			}

			TKey mKey;
			std::shared_ptr<ResourceMap> mResourceMap;
		};
	};
}