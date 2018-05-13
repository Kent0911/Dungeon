#include "Render.h"

using namespace kit;
using namespace kit::Engine;

DirectX::XMMATRIX														kit::Engine::g_mWorld;
DirectX::XMMATRIX														kit::Engine::g_mView;
DirectX::XMMATRIX														kit::Engine::g_mProjection;
ID3D11InputLayout*														kit::Engine::g_pBatchInputLayout;
std::unique_ptr<DirectX::CommonStates>									kit::Engine::g_uptrStates;
std::unique_ptr<DirectX::EffectFactory>									kit::Engine::g_uptrFXFactry;
std::unique_ptr<DirectX::BasicEffect>									kit::Engine::g_uptrBasicEffect;
std::unique_ptr<DirectX::SpriteBatch>									kit::Engine::g_uptrSprites;
std::unique_ptr<DirectX::SpriteFont>									kit::Engine::g_uptrFonts;
std::unique_ptr<DirectX::GeometricPrimitive>							kit::Engine::g_uptrShape;
std::unique_ptr<DirectX::Model>											kit::Engine::g_uptrModel;
std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	kit::Engine::g_uptrBatch;

HRESULT kit::Engine::RenderInitalize() {
	HRESULT hr = S_OK;

	g_uptrStates.reset(new DirectX::CommonStates(g_pd3dDevice));
	g_uptrSprites.reset(new DirectX::SpriteBatch(g_pImmediateContext));
	g_uptrFXFactry.reset(new DirectX::EffectFactory(g_pd3dDevice));
	g_uptrBatch.reset(new DirectX::PrimitiveBatch<DirectX::VertexPositionColor>(g_pImmediateContext));
	g_uptrBasicEffect.reset(new DirectX::BasicEffect(g_pd3dDevice));
	g_uptrBasicEffect->SetVertexColorEnabled(true);
	
	{
		void const* shaderByteCode;
		size_t byteCodeLength;

		g_uptrBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		hr = g_pd3dDevice->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
			DirectX::VertexPositionColor::InputElementCount,
			shaderByteCode, byteCodeLength,
			&g_pBatchInputLayout);

		if (FAILED(hr)) { return hr; }
	}
	g_uptrFonts.reset(new DirectX::SpriteFont(g_pd3dDevice, L"italic.spritefont"));

	return S_OK;
}


DirectX::XMMATRIX kit::Engine::LookVector(CameraStatus* _state) {
	DirectX::XMVECTOR eye = DirectX::XMVectorSet(_state->mvec_position.x, _state->mvec_position.y, _state->mvec_position.z, 0.0f);
	DirectX::XMVECTOR at = DirectX::XMVectorSet(_state->mvec_target.x, _state->mvec_target.y, _state->mvec_target.z, 0.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(_state->mvec_upperVec.x, _state->mvec_upperVec.y, _state->mvec_upperVec.z, 0.0f);
	return DirectX::XMMatrixLookAtLH(eye, at, up);
}

Font::Font(std::string _str, kit::vec2 _pos) {
	m_str = _str;
	mvec_displayPosition = _pos;
	mf_scale = 1.0f;
}

Font::Font(std::string _str, kit::vec2 _pos, float _scale) {
	m_str = _str;
	mvec_displayPosition = _pos;
	mf_scale = _scale;
}

Font::~Font() {

}

DirectX::XMFLOAT2 Font::GetDisplayPos() {
	return DirectX::XMFLOAT2(mvec_displayPosition.x, mvec_displayPosition.y);
}

void Font::DisplayFont(DirectX::XMVECTOR _color) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

	// stirng -> wstirng
	std::wstring wstr = cv.from_bytes(m_str);
	std::wcout.imbue(std::locale(""));

	DirectX::XMFLOAT2 origin = { 0,0 };
	g_uptrFonts->DrawString(g_uptrSprites.get(), wstr.c_str(), GetDisplayPos(), _color, 0.0f, origin, mf_scale);
}

