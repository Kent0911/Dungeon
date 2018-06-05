#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#else
#include <d3d11_1.h>
#endif

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <functional>
#include <memory>
#include <vector>
#include <wincodec.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXHelpers.h>
#include <Windows.h>
#include <algorithm>
#include <GraphicsMemory.h>

#include "../../../Library/DirectXTK/include/CommonStates.h"
#include "../../../Library/DirectXTK/include/VertexTypes.h"
#include "../../../Library/XNAMath/xnamath.h"
#include "../Shader/SpriteEffect_SpriteVertexShader.inc"
#include "../Shader/SpriteEffect_SpritePixelShader.inc"
#include "SharedResourcePool.h"
#include "AlignedNew.h"
#include "ConstantBuffer.h"

enum SpriteSortMode
{
	SpriteSortMode_Deferred,
	SpriteSortMode_Immediate,
	SpriteSortMode_Texture,
	SpriteSortMode_BackToFront,
	SpriteSortMode_FrontToBack,
};


enum SpriteEffects
{
	SpriteEffects_None = 0,
	SpriteEffects_FlipHorizontally = 1,
	SpriteEffects_FlipVertically = 2,
	SpriteEffects_FlipBoth = SpriteEffects_FlipHorizontally | SpriteEffects_FlipVertically,
};

namespace kit {
	namespace Engine {
		// “ÆŽ©•`‰æƒNƒ‰ƒX
		class Sprites {
		public:
			explicit Sprites(_In_ ID3D11DeviceContext* deviceContext);
			Sprites(Sprites&& moveFrom) throw();
			Sprites& operator= (Sprites&& moveFrom) throw();

			Sprites(Sprites const&) = delete;
			Sprites& operator= (Sprites const&) = delete;

			virtual ~Sprites();

			// Bigin/End a batch of sprite drawing operations;
			void XM_CALLCONV Begin(SpriteSortMode sortMode = SpriteSortMode_Deferred, _In_opt_ ID3D11BlendState* blendState = nullptr, _In_opt_ ID3D11SamplerState* samplerState = nullptr, _In_opt_ ID3D11DepthStencilState* depthStencilState = nullptr, _In_opt_ ID3D11RasterizerState* rasterizerState = nullptr,
				_In_opt_ std::function<void __cdecl()> setCustomShaders = nullptr, DirectX::FXMMATRIX transformMatrix = DirectX::XMMatrixIdentity());
			void __cdecl End();

			void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* _texture, DirectX::XMFLOAT2 const& _position, DirectX::FXMVECTOR _color = DirectX::Colors::White);
			void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* _texture, DirectX::XMFLOAT2 const& _position, _In_opt_ RECT const* _sourceRectangle, DirectX::FXMVECTOR _color = DirectX::Colors::White, float _rotation = 0, DirectX::XMFLOAT2 const& _origin = mx_float2Zero, float _scale = 1, SpriteEffects _effects = SpriteEffects_None, float _layerDepth = 0);
			void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* _texture, DirectX::XMFLOAT2 const& _position, _In_opt_ RECT const* _sourceRectangle, DirectX::FXMVECTOR _color, float _rotation, DirectX::XMFLOAT2 const& _origin, DirectX::XMFLOAT2 const& _scale, SpriteEffects _effects = SpriteEffects_None, float _layerDepth = 0);

			void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* _texture, DirectX::XMFLOAT2 _position, DirectX::FXMVECTOR _color = DirectX::Colors::White);

			void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* _texture1, DirectX::XMFLOAT2 const& _position1, DirectX::FXMVECTOR _color1, DirectX::XMFLOAT2 _scale1, _In_ ID3D11ShaderResourceView* _texture2, DirectX::XMFLOAT2 const& _position2, DirectX::FXMVECTOR _color2, DirectX::XMFLOAT2 _scale2);
			
			void __cdecl SetRotation(DXGI_MODE_ROTATION _mode);
			DXGI_MODE_ROTATION __cdecl GetRotation() const;

			void __cdecl SetViewport(const D3D11_VIEWPORT& _viewPort);

		private:
			class Impl;

			std::unique_ptr<Impl>	pImpl;

			static const DirectX::XMMATRIX mx_matrixIdentity;
			static const DirectX::XMFLOAT2 mx_float2Zero;
		};
	}
}