#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#else
#include <d3d11_1.h>
#endif

#include <d3d11.h>
#include <wrl.h>
#include <assert.h>
#include <DirectXHelpers.h>

#include "../../../Library/DirectXTK/include/GraphicsMemory.h"

inline void ThrowIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		throw std::exception();
	}
}

namespace DirectX {

	template<typename T>
	class ConstantBuffer {
	public:
		ConstantBuffer() = default;
		explicit ConstantBuffer(_In_ ID3D11Device* _device) {
			Create(_device);
		}
		ConstantBuffer(ConstantBuffer const&) = delete;
		ConstantBuffer& operator=(ConstantBuffer const&) = delete;

#if defined(_XBOX_ONE) && defined(_TITLE)
		void Create(_In_ ID3D11Device* _device) {
			D3D11_BUFFER_DESC desc = { };

			desc.ByteWidth = sizeof(T);
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			Mircrosoft::MRL::ComPtr<ID3D11DeviceX> deviceX;

			ThrowIfFailed(_device->QueryInterface(IID_GRAOHICS_PPV_ARGS(deviceX.GetAddressOf())));

			ThrowIfFailed(directX->CreatePlacementBuffer(&desc, nullptr, mConstantBuffer.ReleaseAndGetAddressOf()));

			SetDebugObjectName(mConstantBuffer.Get(), L"DirectXTK");
		}

		void SetData(_In_ ID3D11DeviceContext* _deviceContext, T const& _value, void** _grfxMemory) {
			assert(0 != _grfxMemory);

			void* ptr = GraphicsMemory::Get().Allocate(_deviceContext, sizeof(T), 64);
			assert(0 != ptr);

			*(T*)ptr = _value;

			*_grfxMemory = ptr;

		}
#else
		void Create(_In_ ID3D11Device* _device) {
			D3D11_BUFFER_DESC desc = {};
			desc.ByteWidth = sizeof(T);
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			ThrowIfFailed(_device->CreateBuffer(&desc, nullptr, mConstantBuffer.ReleaseAndGetAddressOf()));

			SetDebugObjectName(mConstantBuffer.Get(), "DirectXTK");
		}

		void SetData(_In_ ID3D11DeviceContext* _deviceContext, T const& _value) {

			assert(0 != mConstantBuffer.Get());

			D3D11_MAPPED_SUBRESOURCE mappedResource;

			ThrowIfFailed(_deviceContext->Map(mConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));

			*static_cast<T*>(mappedResource.pData) = _value;

			_deviceContext->Unmap(mConstantBuffer.Get(), 0);
		}

#endif
		ID3D11Buffer* GetBuffer() {
			return mConstantBuffer.Get();
		}
	

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;
	};
}