
#include "Sprite.h"

#include "Framework/Framework.h"

// コンストラクタ
Runtime::Sprite::Sprite()
	: m_position(Vector2(0.0f, 0.0f))
	, m_size(Vector2f(0.0f, 0.0f))
	, m_rotation(0)
{

}
// デストラクター
Runtime::Sprite::~Sprite()
{

}

// 初期化処理
void Runtime::Sprite::Init(
	const Vector2f _size,
	const Vector2f _position,
	const std::string _texturePath,
	const std::string _materialPath
)
{
	if (!m_material.Init(_materialPath))
	{
		printf("[Sprite]：マテリアルの初期化が失敗しました！\n");
		return;
	}

	if (_texturePath != "")
	{
		Render::Texture* pTempTexture = Assets_I->GetTexture(_texturePath);
		if (pTempTexture)
		{
			m_material.SetTexture(pTempTexture);
		}
	}

	m_size = _size;
	m_position = _position;
	m_rotation = 0;

	_initBuffers();
}
// 初期化処理
void Runtime::Sprite::Init(
	const float _sizeX,
	const float _sizeY,
	const float _positionX,
	const float _positionY,
	const std::string _texturePath,
	const std::string _materialPath
)
{
	if (!m_material.Init(_materialPath))
	{
		printf("[Sprite]：マテリアルの初期化が失敗しました！\n");
		return;
	}

	m_size = Vector2f(_sizeX, _sizeY);
	m_position = Vector2f(_positionX, _positionY);
	m_rotation = 0;

	_initBuffers();
}

// スプライトを描画する
void Runtime::Sprite::Draw()
{
	// レンダリングを要求する
	Render_I->QueueRender(this);
}

// テクスチャを設定する
void Runtime::Sprite::SetTexture(Render::Texture* const _pNewTexture)
{
	m_material.SetTexture(_pNewTexture);
}

// 位置を設定する
void Runtime::Sprite::SetPosition(const Vector2f& _position)
{
	m_position = _position;
}
// 位置を設定する
void Runtime::Sprite::SetPosition(const float _x, const float _y)
{
	m_position.x = _x;
	m_position.y = _y;
}
// 回転角度を設定する
void Runtime::Sprite::SetRotation(const int _degree)
{
	m_rotation = _degree;
}
// サイズを設定する
void Runtime::Sprite::SetSize(const Vector2f& _size)
{
	m_size = _size;
}
// サイズを設定する
void Runtime::Sprite::SetSize(const float _x, const float _y)
{
	m_size.x = _x;
	m_size.y = _y;
}


// 位置を取得する
Vector2f Runtime::Sprite::GetPosition() const
{
	return m_position;
}
// サイズを取得する
Vector2f Runtime::Sprite::GetSize() const
{
	return m_size;
}
// 回転角度(逆時計回り)を取得する
int Runtime::Sprite::GetRotation() const
{
	return m_rotation;
}

// テクスチャの表示範囲を指定する
void Runtime::Sprite::SetTextureRange(
	const float _x,
	const float _y,
	const float _width,
	const float _height
)
{
	// 左上
	m_meshData.vertexDatas[0].uv = XMFLOAT2(_x, _y);
	// 右上
	m_meshData.vertexDatas[1].uv = XMFLOAT2(_x + _width, _y);
	// 左下
	m_meshData.vertexDatas[2].uv = XMFLOAT2(_x, _y + _height);
	// 右下
	m_meshData.vertexDatas[3].uv = XMFLOAT2(_x + _width, _y + _height);

	// ヴァーテックスバッファー上にデータを更新する
	m_vertexBuffer.UpdateVertex(
		m_meshData.vertexDatas.data(), 
		m_meshData.vertexDatas.size(), 
		sizeof(VertexData)
	);
}

// レンダリング用のデータを取得する
RenderData Runtime::Sprite::GetData()
{
	RenderData data = {};
	data.vertexBufferView = m_vertexBuffer.GetView();
	data.indexBufferView = m_indexBuffer.GetView();
	data.pConstantBuffer = &m_constantBuffer;
	data.indexNum = 6;
	data.pMaterial = &m_material;

	return data;
}

DirectX::XMMATRIX Runtime::Sprite::GetTransformMatrix() const
{
	XMMATRIX scaleMatrix = DirectX::XMMatrixScaling(
		m_size.x,
		m_size.y,
		1
	);

	XMMATRIX rotateMatrix = DirectX::XMMatrixRotationZ(
		DegToRad((float)m_rotation)
	);

	XMMATRIX translateMatrix = DirectX::XMMatrixTranslation(
		m_position.x,
		m_position.y,
		0.0f
	);

	return scaleMatrix * rotateMatrix * translateMatrix;
}

void Runtime::Sprite::_initBuffers()
{
	// メッシュデータ(Quad)の初期化
	m_meshData.vertexDatas =
	{
		// 左上
		{
			XMFLOAT3(-0.5f,  0.5f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT2(0.0f, 0.0f)
		},
		// 右上
		{
			XMFLOAT3(0.5f,  0.5f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT2(1.0f, 0.0f)
		},
		// 左下
		{
			XMFLOAT3(-0.5f, -0.5f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT2(0.0f, 1.0f)
		},
		// 右下
		{
			XMFLOAT3(0.5f, -0.5f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT2(1.0f, 1.0f)
		}
	};

	// インデクスデータを設定
	m_meshData.indices =
	{
		0, 1, 2,
		2, 1, 3
	};
	

	ID3D12Device* pDevice = Render_I->GetGraphics()->GetDevice();
	if (!m_vertexBuffer.Init(
		pDevice,
		m_meshData.vertexDatas.size(),
		sizeof(VertexData),
		m_meshData.vertexDatas.data()
	))
	{
		printf("【Sprite】：Failed to Init VertexBuffer\n");
		return;
	}

	if (!m_indexBuffer.Init(
		pDevice,
		(UINT)m_meshData.indices.size(),
		sizeof(uint32_t),
		m_meshData.indices.data()
	))
	{
		printf("【Sprite】：Failed to Init IndexBuffer\n");
		return;
	}

	if (!m_constantBuffer.Init(pDevice))
	{
		printf("【Sprite】：Failed to Init ConstantBuffer\n");
		return;
	}
}