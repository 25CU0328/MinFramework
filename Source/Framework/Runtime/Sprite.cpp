
#include "Sprite.h"

#include "Framework.h"

// コンストラクタ
Runtime::Sprite::Sprite()
{

}
// デストラクター
Runtime::Sprite::~Sprite()
{
	
}

// 初期化処理
void Runtime::Sprite::Init(
	const std::string _filePath, 
	const Vector2f _size, 
	const Vector2f _position
)
{
	if (!m_material.Init(_filePath))
	{
		printf("[Sprite]：マテリアルの初期化が失敗しました！\n");
		return;
	}
	if (m_material.GetTexture() == nullptr)
	{
		printf("Fuck Null Pointers\n");
	}
	m_size = _size;
	m_position = _position;
	m_rotation = 0.0f;

	_initBuffers();
}
// 初期化処理
void Runtime::Sprite::Init(
	const std::string _filePath,
	const float _sizeX,
	const float _sizeY,
	const float _positionX,
	const float _positionY
)
{
	if (!m_material.Init(_filePath))
	{
		printf("[Sprite]：マテリアルの初期化が失敗しました！\n");
		return;
	}

	m_size = Vector2f(_sizeX, _sizeY);
	m_position = Vector2f(_positionX, _positionY);
	m_rotation = 0.0f;

	_initBuffers();
}

// スプライトを描画する
void Runtime::Sprite::Draw()
{
	// レンダリングを要求する
	Render_I->QueueRender(this);
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

DirectX::XMMATRIX Runtime::Sprite::GetWorldMatrix()
{
	XMMATRIX scaleMatrix = DirectX::XMMatrixScaling(
		m_size.x,
		m_size.y,
		1
	);

	XMMATRIX rotateMatrix = DirectX::XMMatrixRotationZ(
		DegToRad(m_rotation)
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
	MeshData meshData;
	{
		meshData.vertexDatas =
		{
			{
				XMFLOAT3(-0.5f,  0.5f, 0.0f),
				XMFLOAT3(0.0f, 0.0f, -1.0f),
				XMFLOAT2(0.0f, 0.0f)
			},
			{
				XMFLOAT3(0.5f,  0.5f, 0.0f),
				XMFLOAT3(0.0f, 0.0f, -1.0f),
				XMFLOAT2(1.0f, 0.0f)
			},
			{
				XMFLOAT3(-0.5f, -0.5f, 0.0f),
				XMFLOAT3(0.0f, 0.0f, -1.0f),
				XMFLOAT2(0.0f, 1.0f)
			},
			{
				XMFLOAT3(0.5f, -0.5f, 0.0f),
				XMFLOAT3(0.0f, 0.0f, -1.0f),
				XMFLOAT2(1.0f, 1.0f)
			}
		};

		meshData.indices =
		{
			0, 1, 2,
			2, 1, 3
		};
	}

	ID3D12Device* pDevice = Render_I->GetGraphics()->GetDevice();
	if(!m_vertexBuffer.Init(
		pDevice,
		meshData.vertexDatas.size(),
		sizeof(VertexData),
		meshData.vertexDatas.data()
	))
	{
		printf("【Sprite】：Failed to Init VertexBuffer\n");
		return;
	}

	if (!m_indexBuffer.Init(
		pDevice,
		meshData.indices.size(),
		sizeof(uint32_t),
		meshData.indices.data()
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