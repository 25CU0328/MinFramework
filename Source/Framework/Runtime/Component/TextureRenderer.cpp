
#include "TextureRenderer.h"

// RenderManagerを取得するためインクルード
#include "Framework/Framework.h"

#include "Framework/Assets/AssetData/ComponentData.h"

// コンストラクタ
TextureRenderer::TextureRenderer()
{

}

// デストラクター
TextureRenderer::~TextureRenderer()
{

}

// 初期化する
void TextureRenderer::Init()
{
	MeshData quadMeshData;
	{
		// バーテックスデータを設定する
		quadMeshData.vertexDatas =
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

		// インデクスデータを設定する
		quadMeshData.indices =
		{
			0, 1, 2,
			2, 1, 3
		};
	}

	// クアッドメッシュの初期化
	m_quadMesh.Init(
		Render_I->GetGraphics()->GetDevice(),
		quadMeshData
	);

	// マテリアルの初期化
	m_material.Init("Assets/Materials/SpriteDefaultMaterial.txt");
}

// 描画処理
void TextureRenderer::Render()
{
	Render_I->QueueRender(this);
}

// テクスチャを設定する
void TextureRenderer::SetTexture(Render::Texture* const _pNewTexture)
{
	m_material.SetTexture(_pNewTexture);
}

// レンダリング用のデータを取得する
void TextureRenderer::GetRenderDatas(std::vector<RenderData>& _outRenderDatas) const
{	
	// 引数のベクターは空じゃない場合、ベクターを空にする
	if (!_outRenderDatas.empty())
		_outRenderDatas.clear();

	RenderData tempRenderData;
	{
		tempRenderData.vertexBufferView = m_quadMesh.GetVertexBuffer()->GetView();
		tempRenderData.indexBufferView = m_quadMesh.GetIndexBuffer()->GetView();
		tempRenderData.pConstantBuffer = m_quadMesh.GetConstantBuffer();
		tempRenderData.indexNum = 6;
		tempRenderData.pMaterial = &m_material;
	}

	_outRenderDatas.emplace_back(tempRenderData);
}

// コンポネントデータを取得する
GameComponentData TextureRenderer::GetComponentData() const
{
	TextureRendererData rendererData;
	{
		rendererData.textureFilePath = m_material.GetTexture()->GetFilePath();
	}

	GameComponentData componentData;
	{
		componentData.type = GameComponentType::TextureRenderer;
		componentData.data = rendererData;
	}

	return componentData;
}

// コンポネントを設定する
void TextureRenderer::SetComponent(const GameComponentData _componentData)
{
	TextureRendererData data = _componentData.data.get<TextureRendererData>();

	Render::Texture* pTexture = Assets_I->GetTexture(data.textureFilePath);
	m_material.SetTexture(pTexture);
}