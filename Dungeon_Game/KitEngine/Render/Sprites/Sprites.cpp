#include "Sprites.h"

using namespace kit::Engine;

inline Microsoft::WRL::ComPtr<ID3D11Device> GetDevice(_In_ ID3D11DeviceContext* _deviceContext) {
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	_deviceContext->GetDevice(&device);
	return device;
}

inline DirectX::XMVECTOR LoadRect(_In_ RECT const* _rect) {
	DirectX::XMVECTOR v = DirectX::XMLoadInt4(reinterpret_cast<uint32_t const*>(_rect));

	v = DirectX::XMConvertVectorIntToFloat(v, 0);

	v = DirectX::XMVectorPermute<0, 1, 4, 5>(DirectX::XMVectorZero(), v);

	return v;
}

__declspec(align(16)) class Sprites::Impl :public DirectX::AlignedNew<Sprites::Impl> {
public:
	Impl(_In_ ID3D11DeviceContext* _deviceContext);

	void XM_CALLCONV Begin(SpriteSortMode _sortMode,
		_In_opt_ ID3D11BlendState* _blendState,
		_In_opt_ ID3D11SamplerState* _samplaerState,
		_In_opt_ ID3D11DepthStencilState* _depthStencilState,
		_In_opt_ ID3D11RasterizerState* _rasterizerState,
		std::function<void()>& _setCustomShaders,
		DirectX::FXMMATRIX _transformMatrix);
	void End();

	void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* _texture,
		DirectX::FXMVECTOR _destination,
		_In_opt_ RECT const* _sourceRectangle,
		DirectX::FXMVECTOR _color,
		DirectX::FXMVECTOR _originRotationDepth,
		int _flags);

	__declspec(align(16)) struct SpriteInfo : public DirectX::AlignedNew<SpriteInfo> {
		DirectX::XMFLOAT4A source;
		DirectX::XMFLOAT4A destination;
		DirectX::XMFLOAT4A color;
		DirectX::XMFLOAT4A originRotationDepth;
		ID3D11ShaderResourceView* texture;
		int flags;

		static const int SourceInTexels = 4;
		static const int DestSizeInPixels = 8;

		static_assert((SpriteEffects_FlipBoth & (SourceInTexels | DestSizeInPixels)) == 0, "Flag bits must not overlap");
	};

	DXGI_MODE_ROTATION md_rotation;

	bool mb_setViewport;
	D3D11_VIEWPORT md_viewPort;

private:
	void GrowSpriteQueue();
	void PrePareForRendering();
	void Flushbatch();
	void SortSprites();
	void GrowSortedSprites();

	void RenderBatch(_In_ ID3D11ShaderResourceView* _texture, _In_reads_(_count) SpriteInfo const* const* _sprites, size_t _count);

	static void XM_CALLCONV RenderSprite(_In_ SpriteInfo const * _sprite,
		_Out_writes_(VerticesPerSprite) DirectX::VertexPositionColorTexture* _vertices,
		DirectX::FXMVECTOR _textureSize,
		DirectX::FXMVECTOR _inverseTextureSize);

	static DirectX::XMVECTOR GetTextureSize(_In_ ID3D11ShaderResourceView* _texture);
	DirectX::XMMATRIX GetViewportTransform(_In_ ID3D11DeviceContext* _deviceContext, DXGI_MODE_ROTATION _rotation);

	static const size_t MaxBatchSize = 2048;
	static const size_t MinBatchSize = 128;
	static const size_t InitialQueueSize = 64;
	static const size_t VerticesPerSprite = 4;
	static const size_t IndicesPerSprite = 6;


	std::unique_ptr<SpriteInfo[]> muptr_spriteQueue;

	size_t m_spriteQueueCount;
	size_t m_spriteQueueArraySize;


	std::vector<SpriteInfo const*> mv_sortedSprites;

	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mv_spriteTextureReferences;

	bool mb_inBeginEndPair;

	SpriteSortMode m_sortMode;
	Microsoft::WRL::ComPtr<ID3D11BlendState>			m_blendState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			m_samlperState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		m_depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		m_rasterizerState;
	std::function<void()>								m_setCustomShaders;
	DirectX::XMMATRIX									m_transformMatrix;


	struct DeviceResources {
		DeviceResources(_In_ ID3D11Device* _device);

		Microsoft::WRL::ComPtr<ID3D11VertexShader>	vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	pixelShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		indexBuffer;

		DirectX::CommonStates						stateOjects;

	private:
		void CreateShaders(_In_ ID3D11Device* _device);
		void CreateIndexBuffer(_In_ ID3D11Device* _device);

		static std::vector<short> CreateIndexValues();
	};

	struct ContextResources {
		ContextResources(_In_ ID3D11DeviceContext* _deviceContext);

#if defined(_XBOX_ONE) && defined(_TITLE)
		Microsoft::WRL::ComPtr<ID3D11DeviceContextX> deviceContext;
#else
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
#endif

		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	
		DirectX::ConstantBuffer<DirectX::XMMATRIX> constantBuffer;

		size_t vertexBufferPosition;

		bool inImmedateMode;


	private:
		void CreateVertexBuffer();
	};


	std::shared_ptr<DeviceResources> m_deviceResources;
	std::shared_ptr<ContextResources> m_contextResources;

	static DirectX::SharedResourcePool<ID3D11Device*, DeviceResources> deviceResourcesPool;
	static DirectX::SharedResourcePool<ID3D11DeviceContext*, ContextResources> contextResourcesPool;
	
};

const DirectX::XMMATRIX Sprites::mx_matrixIdentity = DirectX::XMMatrixIdentity();
const DirectX::XMFLOAT2 Sprites::mx_float2Zero(0, 0);

Sprites::Impl::DeviceResources::DeviceResources(_In_ ID3D11Device* _device) :stateOjects(_device) {
	CreateShaders(_device);
	CreateIndexBuffer(_device);
}

void Sprites::Impl::DeviceResources::CreateShaders(_In_ ID3D11Device* _device) {
	ThrowIfFailed(_device->CreateVertexShader(SpriteEffect_SpriteVertexShader,
		sizeof(SpriteEffect_SpriteVertexShader),
		nullptr,
		&vertexShader));

	ThrowIfFailed(_device->CreatePixelShader(SpriteEffect_SpritePixelShader,
		sizeof(SpriteEffect_SpritePixelShader),
		nullptr,
		&pixelShader));
	
	ThrowIfFailed(_device->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
		DirectX::VertexPositionColorTexture::InputElementCount,
		SpriteEffect_SpriteVertexShader,
		sizeof(SpriteEffect_SpriteVertexShader),
		&inputLayout));

	DirectX::SetDebugObjectName(vertexShader.Get(), "kitEngine:Sprites");
	DirectX::SetDebugObjectName(pixelShader.Get(), "kitEngine:Sprites");
	DirectX::SetDebugObjectName(inputLayout.Get(), "kitEngine:Sprites");
}

void Sprites::Impl::DeviceResources::CreateIndexBuffer(_In_ ID3D11Device* _device) {
	D3D11_BUFFER_DESC indexBufferDesc = {};

	static_assert((MaxBatchSize * VerticesPerSprite) < USHRT_MAX, "MaxBatchSize too large for 16-bit indices");

	indexBufferDesc.ByteWidth = sizeof(short) * MaxBatchSize * IndicesPerSprite;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	auto indexValues = CreateIndexValues();

	D3D11_SUBRESOURCE_DATA indexDadaDesc = {};

	indexDadaDesc.pSysMem = indexValues.data();

	ThrowIfFailed(_device->CreateBuffer(&indexBufferDesc, &indexDadaDesc, &indexBuffer));

	DirectX::SetDebugObjectName(indexBuffer.Get(), "kitEngine:Sprites");
}

std::vector<short> Sprites::Impl::DeviceResources::CreateIndexValues() {
	std::vector<short> indices;

	indices.reserve(MaxBatchSize * IndicesPerSprite);

	for (short s = 0; s < MaxBatchSize * VerticesPerSprite; s += VerticesPerSprite) {
		indices.push_back(s);
		indices.push_back(s + 1);
		indices.push_back(s + 2);

		indices.push_back(s + 1);
		indices.push_back(s + 3);
		indices.push_back(s + 2);
	}
	return indices;
}

Sprites::Impl::ContextResources::ContextResources(_In_ ID3D11DeviceContext* _context) :constantBuffer(GetDevice(_context).Get()),vertexBufferPosition(0),inImmedateMode(false) {
#if defined(_XBOX_ONE) && defined(_TITLE)
	ThrowIfFailed(_context->QueryInterface(IID_GRAPHICS_PPV_ARGS(deviceContext.GetAddressOf())));
#else
	deviceContext = _context;
#endif
	CreateVertexBuffer();
}



void Sprites::Impl::ContextResources::CreateVertexBuffer() {
#if defined(_XBOX_ONE) && defined(_TITLE)
	D3D11_BUFFER_DESC vertexBufferDesc = {};

	vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * MaxBatchSize * VerticesPerSprite;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFALUT;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	auto device = GetDevice(deviceContext.Get());

	Microsoft::WRL::ComPtr<Id3D11DeviceX> deviceX;
	ThrowIfFailed(device.As(&deviceX));

	ThrowIfFailed(deviceX->CreatePlacementBuffer(&vertexBufferDesc, nullptr, &vertexBuffer));

	DirectX::SetDebugObjectName(vertexBuffer.Get(), "kitEngine:Sprites");
#else
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * MaxBatchSize * VerticesPerSprite;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ThrowIfFailed(GetDevice(deviceContext.Get())->CreateBuffer(&vertexBufferDesc, nullptr, &vertexBuffer));

	DirectX::SetDebugObjectName(vertexBuffer.Get(), "kitEngine:Sprites");
#endif
}


Sprites::Impl::Impl(_In_ ID3D11DeviceContext* _deviceContext)
	:	md_rotation(DXGI_MODE_ROTATION_IDENTITY),
		mb_setViewport(false),
	md_viewPort{},
	m_spriteQueueCount(0),
	m_spriteQueueArraySize(0),
	mb_inBeginEndPair(false),
	m_sortMode(SpriteSortMode_Deferred),
	m_transformMatrix(DirectX::XMMatrixIdentity()),
	m_deviceResources(deviceResourcesPool.DemandCreate(GetDevice(_deviceContext).Get())),
	m_contextResources(contextResourcesPool.DemandCreate(_deviceContext)){

}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Impl::Begin(SpriteSortMode _sortMode,
	ID3D11BlendState* _blendState,
	ID3D11SamplerState* _samplerState,
	ID3D11DepthStencilState* _depthStencilState,
	ID3D11RasterizerState* _rasterizerState,
	std::function<void()>& _setCustomShaders,
	DirectX::FXMMATRIX _transformMatrix) {
	if (mb_inBeginEndPair) {
		throw std::exception("Cannot nest Begin calls on a single Sprites");
	}

	m_sortMode = _sortMode;
	m_blendState = _blendState;
	m_samlperState = _samplerState;
	m_depthStencilState = _depthStencilState;
	m_rasterizerState = _rasterizerState;
	m_setCustomShaders = _setCustomShaders;
	m_transformMatrix = _transformMatrix;

	if (SpriteSortMode_Immediate == _sortMode) {
		if (m_contextResources->inImmedateMode) {
			throw std::exception("Only one Sprites at a time can use SpriteSortMode_Immediate");
		}

		PrePareForRendering();

		m_contextResources->inImmedateMode = true;
	}

	mb_inBeginEndPair = true;
}

void Sprites::Impl::End() {
	if (!mb_inBeginEndPair) {
		throw std::exception("Begin must be called Before End");
	}
	if (SpriteSortMode_Immediate == m_sortMode) {
		m_contextResources->inImmedateMode = false;
	}
	else {
		if (m_contextResources->inImmedateMode) {
			throw std::exception("Cannot end one Sprites while another is using SpriteSortMode_Immediate");
		}

		PrePareForRendering();
		Flushbatch();
	}

	m_setCustomShaders = nullptr;
	mb_inBeginEndPair = false;
}


_Use_decl_annotations_
void XM_CALLCONV Sprites::Impl::Draw(ID3D11ShaderResourceView* _texture,
		DirectX::FXMVECTOR _destination,
		RECT const* _sourceRectangle,
		DirectX::FXMVECTOR _color,
		DirectX::FXMVECTOR _originRotationDepth,
		int _flags) {
	if (!_texture) {
		throw std::exception("Texture cannot be null");
	}
	if (!mb_inBeginEndPair) {
		throw std::exception("Begin must be called before Draw");
	}

	if (m_spriteQueueCount >= m_spriteQueueArraySize) {
		GrowSpriteQueue();
	}

	SpriteInfo* sprite = &muptr_spriteQueue[m_spriteQueueCount];

	DirectX::XMVECTOR dest = _destination;
	if (_sourceRectangle) {
		DirectX::XMVECTOR source = LoadRect(_sourceRectangle);

		DirectX::XMStoreFloat4A(&sprite->source, source);

		if (!(_flags & SpriteInfo::DestSizeInPixels)) {
			dest = DirectX::XMVectorPermute<0, 1, 6, 7>(dest, dest * source);
		}

		_flags |= SpriteInfo::SourceInTexels | SpriteInfo::DestSizeInPixels;
	}
	else {
		static const DirectX::XMVECTORF32 wholeTexture{ {{0,0,1,1}} };

		XMStoreFloat4A(&sprite->source, wholeTexture);
	}

	XMStoreFloat4A(&sprite->destination, dest);
	XMStoreFloat4A(&sprite->color, _color);
	XMStoreFloat4A(&sprite->originRotationDepth, _originRotationDepth);

	sprite->texture = _texture;
	sprite->flags = _flags;

	if (SpriteSortMode_Immediate == m_sortMode) {
		RenderBatch(_texture, &sprite, 1);
	}
	else {
		m_spriteQueueCount++;
		if (mv_spriteTextureReferences.empty() || _texture != mv_spriteTextureReferences.back().Get()) {
			mv_spriteTextureReferences.emplace_back(_texture);
		}
	}
}

void Sprites::Impl::GrowSpriteQueue() {
	size_t newSize = (std::max)(InitialQueueSize, m_spriteQueueArraySize * 2);

	std::unique_ptr<SpriteInfo[]> newArray(new SpriteInfo[newSize]);

	for (size_t s = 0; s < m_spriteQueueCount; ++s) {
		newArray[s] = muptr_spriteQueue[s];
	}

	muptr_spriteQueue = std::move(newArray);
	m_spriteQueueArraySize = newSize;

	mv_sortedSprites.clear();
}

void Sprites::Impl::PrePareForRendering() {
	auto deviceContext = m_contextResources->deviceContext.Get();

	auto blendState = m_blendState ? m_blendState.Get() : m_deviceResources->stateOjects.AlphaBlend();
	auto depthStencilState = m_depthStencilState ? m_depthStencilState.Get() : m_deviceResources->stateOjects.DepthNone();
	auto rasterizerState = m_rasterizerState ? m_rasterizerState.Get() : m_deviceResources->stateOjects.CullCounterClockwise();
	auto samlperState = m_samlperState ? m_samlperState.Get() : m_deviceResources->stateOjects.LinearClamp();

	deviceContext->OMGetBlendState(&blendState, nullptr, (UINT*)0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(depthStencilState, 0);
	deviceContext->RSSetState(rasterizerState);
	deviceContext->PSSetSamplers(0, 1, &samlperState);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetInputLayout(m_deviceResources->inputLayout.Get());
	deviceContext->VSSetShader(m_deviceResources->vertexShader.Get(), nullptr, 0);
	deviceContext->PSSetShader(m_deviceResources->pixelShader.Get(), nullptr, 0);

#if !defined(_XBOX_ONE) || !defined(_TITLE)
	auto vertexBuffer = m_contextResources->vertexBuffer.Get();
	UINT vertexStride = sizeof(DirectX::VertexPositionColorTexture);
	UINT vertexOffset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);
#endif

	deviceContext->IASetIndexBuffer(m_deviceResources->indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	DirectX::XMMATRIX transformMatrix = (DXGI_MODE_ROTATION_UNSPECIFIED == md_rotation)
		? m_transformMatrix
		: (m_transformMatrix * GetViewportTransform(deviceContext, md_rotation));

#if defined(_XBOX_ONE) && defined(_TITLE)
	void* grfxMemory;
	m_contextResources->constantBuffer.SetData(deviceContext, transformMatrix, &grfxMemory);

	deviceContext->VSSetPlacementConstantBuffer(0, m_contextResources->constantBuffer.GetBuffer(), grfxMemory);
#else
	m_contextResources->constantBuffer.SetData(deviceContext, transformMatrix);

	ID3D11Buffer* constantBuffer = m_contextResources->constantBuffer.GetBuffer();

	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
#endif

	if (D3D11_DEVICE_CONTEXT_DEFERRED == deviceContext->GetType()) {
		m_contextResources->vertexBufferPosition = 0;
	}

	if (m_setCustomShaders) { m_setCustomShaders(); }

}

void Sprites::Impl::Flushbatch() {
	if (!m_spriteQueueCount) { return; }

	SortSprites();

	ID3D11ShaderResourceView* batchTexture = nullptr;
	size_t batchStart = 0;

	for (size_t pos = 0; pos < m_spriteQueueCount; ++pos) {
		ID3D11ShaderResourceView* texture = mv_sortedSprites[pos]->texture;

		_Analysis_assume_(texture != nullptr);
		
		if (texture != batchTexture) {
			if (pos > batchStart) {
				RenderBatch(batchTexture, &mv_sortedSprites[batchStart], pos - batchStart);
			}

			batchTexture = texture;
			batchStart = pos;
		}
	}

	RenderBatch(batchTexture, &mv_sortedSprites[batchStart], m_spriteQueueCount - batchStart);

	m_spriteQueueCount = 0;
	mv_spriteTextureReferences.clear();

	if (SpriteSortMode_Deferred != m_sortMode) {
		mv_sortedSprites.clear();
	}
}

void Sprites::Impl::SortSprites() {
	if (mv_sortedSprites.size() < m_spriteQueueCount) {
		GrowSortedSprites();
	}
	switch (m_sortMode) {
	case SpriteSortMode_Texture:
		std::sort(mv_sortedSprites.begin(), mv_sortedSprites.begin() + m_spriteQueueCount, [](SpriteInfo const* x, SpriteInfo const* y)-> bool {
			return x->texture < y->texture;
		});
		break;

	case SpriteSortMode_BackToFront:
		std::sort(mv_sortedSprites.begin(), mv_sortedSprites.begin() + m_spriteQueueCount, [](SpriteInfo const* x, SpriteInfo const* y)-> bool {
			return x->originRotationDepth.w > y->originRotationDepth.w;
		});
		break;

	case SpriteSortMode_FrontToBack:
		std::sort(mv_sortedSprites.begin(), mv_sortedSprites.begin() + m_spriteQueueCount, [](SpriteInfo const* x, SpriteInfo const* y)-> bool {
			return x->originRotationDepth.w < y->originRotationDepth.w;
		});
		break;

	default:
		break;
	}
}

void Sprites::Impl::GrowSortedSprites() {
	size_t previousSize = mv_sortedSprites.size();

	mv_sortedSprites.resize(m_spriteQueueCount);

	for (size_t s = previousSize; s < m_spriteQueueCount; ++s) {
		mv_sortedSprites[s] = &muptr_spriteQueue[s];
	}
}

_Use_decl_annotations_
void Sprites::Impl::RenderBatch(ID3D11ShaderResourceView* _texture, SpriteInfo const* const* _sprites, size_t _count) {
	auto deviceContext = m_contextResources->deviceContext.Get();

	deviceContext->PSSetShaderResources(0, 1, &_texture);

	DirectX::XMVECTOR textureSize = GetTextureSize(_texture);
	DirectX::XMVECTOR inverseTextureSize = XMVectorReciprocal(textureSize);

	while (_count > 0) {
		size_t batchSize = _count;
		size_t remainingSpace = MaxBatchSize - m_contextResources->vertexBufferPosition;

		if (batchSize > remainingSpace) {
			if (remainingSpace < MinBatchSize) {
				m_contextResources->vertexBufferPosition = 0;

				batchSize = (std::min)(_count, MaxBatchSize);
			}
			else {
				batchSize = remainingSpace;
			}
		}
#if defined(_XBOX_ONE) && defined(_TITLE)
		void* grfxMemory = GraphicsMemory::Get().Allocate(deviceContext, sizeof(DirectX::VertexPositionColorTexture) * batchSize * VerticesPerSprite * 64);
		auto vertices = static_cast<DirectX::VertexPositionColorTexture*>(grfxMemory);
#else
		D3D11_MAP mapType = (m_contextResources->vertexBufferPosition == 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;

		D3D11_MAPPED_SUBRESOURCE mappedBuffer;

		ThrowIfFailed(deviceContext->Map(m_contextResources->vertexBuffer.Get(), 0, mapType, 0, &mappedBuffer));

		auto vertices = static_cast<DirectX::VertexPositionColorTexture*>(mappedBuffer.pData) + m_contextResources->vertexBufferPosition * VerticesPerSprite;
#endif
		for (size_t s = 0; s < batchSize; ++s) {
			assert(s < _count);
			_Analysis_assume_(s < _count);
			RenderSprite(_sprites[s], vertices, textureSize, inverseTextureSize);

			vertices += VerticesPerSprite;
		}

#if defined(_XBOX_ONE) && defined(_TITLE)
		deviceContext->IASetPlacementVertexBuffer(0, m_contextResources->vertexBuffer.Get(), grfxMemory, sizeof(DirectX::VertexPositionColorTexture));
#else
		deviceContext->Unmap(m_contextResources->vertexBuffer.Get(), 0);
#endif

		UINT startIndex = (UINT)m_contextResources->vertexBufferPosition * IndicesPerSprite;
		UINT indexCount = (UINT)batchSize * IndicesPerSprite;

		deviceContext->DrawIndexed(indexCount, startIndex, 0);

#if !defined(_XBOX_ONE) || !defined(_TITLE)
		m_contextResources->vertexBufferPosition += batchSize;
#endif

		_sprites += batchSize;
		_count -= batchSize;
	}
}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Impl::RenderSprite(SpriteInfo const* _sprite,
	DirectX::VertexPositionColorTexture* _vertices,
	DirectX::FXMVECTOR _textureSize,
	DirectX::FXMVECTOR _inverseTextureSize) {
	DirectX::XMVECTOR source = XMLoadFloat4A(&_sprite->source);
	DirectX::XMVECTOR destination = XMLoadFloat4A(&_sprite->destination);
	DirectX::XMVECTOR color = XMLoadFloat4A(&_sprite->color);
	DirectX::XMVECTOR originRotationDepth = XMLoadFloat4A(&_sprite->originRotationDepth);

	float rotation = _sprite->originRotationDepth.z;
	int flags = _sprite->flags;

	DirectX::XMVECTOR sourceSize = XMVectorSwizzle<2, 3, 2, 3>(source);
	DirectX::XMVECTOR destinationSize = XMVectorSwizzle<2, 3, 2, 3>(destination);

	DirectX::XMVECTOR isZeroMask = XMVectorEqual(sourceSize, XMVectorZero());
	DirectX::XMVECTOR nonZeroSourceSize = XMVectorSelect(sourceSize, g_XMEpsilon, isZeroMask);

	DirectX::XMVECTOR origin = XMVectorDivide(originRotationDepth, nonZeroSourceSize);

	if (flags & SpriteInfo::SourceInTexels) {
		source *= _inverseTextureSize;
		sourceSize *= _inverseTextureSize;
	}
	else {
		origin *= _inverseTextureSize;
	}

	if (!(flags & SpriteInfo::DestSizeInPixels)) {
		destinationSize *= _textureSize;
	}

	DirectX::XMVECTOR rotationMatrix1;
	DirectX::XMVECTOR rotationMatrix2;

	if (0 != rotation) {
		float sin, cos;

		XMScalarSinCos(&sin, &cos, rotation);

		DirectX::XMVECTOR sinV = XMLoadFloat(&sin);
		DirectX::XMVECTOR cosV = XMLoadFloat(&cos);

		rotationMatrix1 = XMVectorMergeXY(cosV, sinV);
		rotationMatrix2 = XMVectorMergeXY(-sinV, cosV);
	}
	else {
		rotationMatrix1 = g_XMIdentityR0;
		rotationMatrix2 = g_XMIdentityR1;
	}

	static XMVECTORF32 cornerOffsets[VerticesPerSprite] =
	{
		{{{0,0,0,0}}},
		{{{1,0,0,0}}},
		{{{0,1,0,0}}},
		{{{1,1,0,0}}},
	};

	static_assert(1 == SpriteEffects_FlipHorizontally &&
		2 == SpriteEffects_FlipVertically, "If you change these enum values,the mirroring implemetation must be updated to match");

	int mirrorBits = flags & 3;

	for (int i = 0; i < VerticesPerSprite; ++i) {
		DirectX::XMVECTOR cornerOffset = (cornerOffsets[i] - origin) * destinationSize;

		DirectX::XMVECTOR position1 = XMVectorMultiplyAdd(XMVectorSplatX(cornerOffset), rotationMatrix1, destination);
		DirectX::XMVECTOR position2 = XMVectorMultiplyAdd(XMVectorSplatY(cornerOffset), rotationMatrix2, position1);

		DirectX::XMVECTOR position = XMVectorPermute<0, 1, 7, 6>(position2, originRotationDepth);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_vertices[i].position), position);

		XMStoreFloat4(&_vertices[i].color, color);

		DirectX::XMVECTOR textureCoordinate = XMVectorMultiplyAdd(cornerOffsets[i ^ mirrorBits], sourceSize, source);

		XMStoreFloat2(&_vertices[i].textureCoordinate, textureCoordinate);
	}
}



DirectX::XMVECTOR Sprites::Impl::GetTextureSize(_In_ ID3D11ShaderResourceView* _texture) {
	Microsoft::WRL::ComPtr<ID3D11Resource> resouce;

	_texture->GetResource(&resouce);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;

	if (FAILED(resouce.As(&texture2D))) {
		throw std::exception("Sprites can only draw Texture2D resources");
	}

	D3D11_TEXTURE2D_DESC desc;
	texture2D->GetDesc(&desc);

	DirectX::XMVECTOR size = XMVectorMergeXY(XMLoadInt(&desc.Width), XMLoadInt(&desc.Height));

	return XMConvertVectorUIntToFloat(size, 0);
}



DirectX::XMMATRIX Sprites::Impl::GetViewportTransform(_In_ ID3D11DeviceContext* _deviceContext, DXGI_MODE_ROTATION _rotation) { 
     if (!mb_setViewport) { 
         UINT viewportCount = 1; 
 
 
		 _deviceContext->RSGetViewports(&viewportCount, &md_viewPort);
 
 
		 if (viewportCount != 1) { throw std::exception("No viewport is set"); }
     } 
 

     float xScale = (md_viewPort.Width > 0) ? 2.0f / md_viewPort.Width : 0.0f; 
     float yScale = (md_viewPort.Height > 0) ? 2.0f / md_viewPort.Height : 0.0f; 
 
 
     switch (_rotation) { 
         case DXGI_MODE_ROTATION_ROTATE90: 
             return DirectX::XMMATRIX 
             ( 
                 0, -yScale, 0, 0, 
                 -xScale, 0, 0, 0, 
                 0, 0, 1, 0, 
                 1, 1, 0, 1 
             ); 
 
 
         case DXGI_MODE_ROTATION_ROTATE270: 
             return DirectX::XMMATRIX 
             ( 
                 0, yScale, 0, 0, 
                 xScale, 0, 0, 0, 
                 0, 0, 1, 0, 
                 -1, -1, 0, 1 
             ); 
 

         case DXGI_MODE_ROTATION_ROTATE180: 
             return DirectX::XMMATRIX 
             ( 
                 -xScale, 0, 0, 0, 
                 0, yScale, 0, 0, 
                 0, 0, 1, 0, 
                 1, -1, 0, 1 
             ); 
 

         default: 
             return DirectX::XMMATRIX 
             ( 
                 xScale, 0, 0, 0, 
                 0, -yScale, 0, 0, 
                 0, 0, 1, 0, 
                 -1, 1, 0, 1 
             ); 
     } 
 } 


Sprites::Sprites(_In_ ID3D11DeviceContext* _deviceContext) :pImpl(std::make_unique<Impl>(_deviceContext)) {

}

Sprites::Sprites(Sprites&& _moveFrom) noexcept :pImpl(std::move(_moveFrom.pImpl)) {

}

Sprites& Sprites::operator= (Sprites&& _moveFrom) noexcept {
	pImpl = std::move(_moveFrom.pImpl);
	return *this;
}

Sprites::~Sprites() {

}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Begin(SpriteSortMode _sortMode,
	ID3D11BlendState* _blendState,
	ID3D11SamplerState* _samplerState,
	ID3D11DepthStencilState* _depthStencilState,
	ID3D11RasterizerState* _rasterizerState,
	std::function<void()> _setCustomShaders,
	DirectX::FXMMATRIX _transformMatirx) {
	pImpl->Begin(_sortMode, _blendState, _samplerState, _depthStencilState, _rasterizerState, _setCustomShaders, _transformMatirx);
}

void Sprites::End() {
	pImpl->End();
}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Draw(ID3D11ShaderResourceView* _texture, DirectX::XMFLOAT2 const& _position, DirectX::FXMVECTOR _color) {
	DirectX::XMVECTOR destination = XMVectorPermute<0, 1, 4, 5>(XMLoadFloat2(&_position), g_XMOne);

	pImpl->Draw(_texture, destination, nullptr, _color, g_XMZero, 0);
}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Draw(ID3D11ShaderResourceView* _texture, 
	DirectX::XMFLOAT2 const& _position, 
	RECT const* _sourceRectangle,
	DirectX::FXMVECTOR _color,
	float _rotation,
	DirectX::XMFLOAT2 const& _origin,
	float _scale,
	SpriteEffects _effects,
	float _layerDepth) {
	DirectX::XMVECTOR destination = XMVectorPermute<0, 1, 4, 4>(XMLoadFloat2(&_position), XMLoadFloat(&_scale));
	
	DirectX::XMVECTOR originRotationDepth = XMVectorSet(_origin.x, _origin.y, _rotation, _layerDepth);

	pImpl->Draw(_texture, destination, _sourceRectangle, _color, originRotationDepth, _effects);
}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Draw(ID3D11ShaderResourceView* _texture,
	DirectX::XMFLOAT2 const& _position,
	RECT const* _sourceRectangle,
	DirectX::FXMVECTOR _color,
	float _rotation,
	DirectX::XMFLOAT2 const& _origin,
	DirectX::XMFLOAT2 const& _scale,
	SpriteEffects _effects,
	float _layerDepth) {
	DirectX::XMVECTOR destination = XMVectorPermute<0, 1, 4, 5>(XMLoadFloat2(&_position), XMLoadFloat2(&_scale));

	DirectX::XMVECTOR originRotationDepth = XMVectorSet(_origin.x, _origin.y, _rotation, _layerDepth);

	pImpl->Draw(_texture, destination, _sourceRectangle, _color, originRotationDepth, _effects);
}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Draw(ID3D11ShaderResourceView* _texture, DirectX::XMFLOAT2 _position, DirectX::FXMVECTOR _color) {
	DirectX::XMVECTOR destination = XMVectorPermute<0, 1, 4, 5>(XMLoadFloat2(&_position), g_XMOne);
	pImpl->Draw(_texture, destination, nullptr, _color, g_XMZero, 0);
}

_Use_decl_annotations_
void XM_CALLCONV Sprites::Draw(ID3D11ShaderResourceView* _texture1, DirectX::XMFLOAT2 const& _position1, DirectX::FXMVECTOR _color1,DirectX::XMFLOAT2 _scale1,
	ID3D11ShaderResourceView* _texture2, DirectX::XMFLOAT2 const& _position2, DirectX::FXMVECTOR _color2, DirectX::XMFLOAT2 _scale2) {
	DirectX::XMVECTOR destination1 = XMVectorPermute<0, 1, 4, 5>(XMLoadFloat2(&_position1), XMLoadFloat2(&_scale1));
	DirectX::XMVECTOR destination2 = XMVectorPermute<0, 1, 4, 5>(XMLoadFloat2(&_position2), XMLoadFloat2(&_scale2));

	_color1 * _color2;

	pImpl->Draw(_texture1, destination1, nullptr, _color1, g_XMZero, 0);
	pImpl->Draw(_texture2, destination2, nullptr, _color2, g_XMZero, 0);
}

void Sprites::SetRotation(DXGI_MODE_ROTATION _mode) {
	pImpl->md_rotation = _mode;
}

DXGI_MODE_ROTATION Sprites::GetRotation() const {
	return pImpl->md_rotation;
}

void Sprites::SetViewport(const D3D11_VIEWPORT& _viewPort) {
	pImpl->mb_setViewport = true;
	pImpl->md_viewPort = _viewPort;
}


