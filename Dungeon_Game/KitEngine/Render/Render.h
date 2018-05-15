#pragma once

#include <d3d11.h>
#include <memory>
#include <string>
#include <locale>
#include <codecvt>

#include "../KitEngine.h"
#include "../../Library/DirectXTK/include/CommonStates.h"
#include "../../Library/DirectXTK/include/Effects.h"
#include "../../Library/DirectXTK/include/SimpleMath.h"
#include "../../Library/DirectXTK/include/SpriteBatch.h"
#include "../../Library/DirectXTK/include/SpriteFont.h"
#include "../../Library/DirectXTK/include/Model.h"
#include "../../Library/DirectXTK/include/PrimitiveBatch.h"
#include "../../Library/DirectXTK/include/GeometricPrimitive.h"
#include "../../Library/DirectXTK/include/ScreenGrab.h"
#include "../../Library/DirectXTK/include/VertexTypes.h"
#include "../../Library/KitLib/include/Kitlib.h"
#include "Fonts\Fonts.h"


namespace kit {
	namespace Engine {
		extern DirectX::XMMATRIX														g_mWorld;
		extern DirectX::XMMATRIX														g_mView;
		extern DirectX::XMMATRIX														g_mProjection;
		extern ID3D11InputLayout*														g_pBatchInputLayout;
		extern std::unique_ptr<DirectX::CommonStates>									g_uptrStates;
		extern std::unique_ptr<DirectX::EffectFactory>									g_uptrFXFactry;
		extern std::unique_ptr<DirectX::BasicEffect>									g_uptrBasicEffect;
		extern std::unique_ptr<DirectX::SpriteBatch>									g_uptrSprites;
		extern std::unique_ptr<DirectX::SpriteFont>										g_uptrFonts;
		extern std::unique_ptr<DirectX::GeometricPrimitive>								g_uptrShape;
		extern std::unique_ptr<DirectX::Model>											g_uptrModel;
		extern std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	g_uptrBatch;
		

		class CameraStatus {
		public:
			kit::vec3 mvec_position;
			kit::vec3 mvec_target;
			kit::vec3 mvec_upperVec;
		};

		HRESULT RenderInitalize();

		DirectX::XMMATRIX LookVector(CameraStatus* _state);
	}
}