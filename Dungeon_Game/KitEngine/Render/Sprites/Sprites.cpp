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