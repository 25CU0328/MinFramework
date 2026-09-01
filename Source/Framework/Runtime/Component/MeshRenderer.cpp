
#include "MeshRenderer.h"

#include "Framework/Framework.h"
#include "Framework/Math/Math.h"

// メッシュを描画する
void MeshRenderer::Render()
{
	Render_I->QueueRender(this);
}

// 描画するメッシュを設定する
void MeshRenderer::SetMesh(const ModelData& _modelData)
{
	if (!m_pMeshes.empty())
	{
		for (Mesh*& pMesh : m_pMeshes)
		{
			delete pMesh;
		}

		m_pMeshes.clear();
	}

	// レンダリングマネージャーからデバイスを取得する
	ID3D12Device* pDevice = Render_I->GetGraphics()->GetDevice();

	// モデルのメッシュデータでメッシュを生成・初期化する
	for (MeshData meshData : _modelData.meshDatas)
	{
		m_pMeshes.emplace_back(new Mesh());

		m_pMeshes.back()->Init(pDevice, meshData);
	}

	// ファイルパスを保存する
	m_filePath = _modelData.filePath;
}

// マテリアルを設定する
void MeshRenderer::SetMaterial(const std::string _materialName)
{
	m_material.Init(_materialName);
}

// テクスチャを設定する
void MeshRenderer::SetTexture(std::string _texturePath)
{
	Render::Texture* pTexture = Assets_I->GetTexture(_texturePath);

	if(!pTexture)
	{
		printf("【MeshRenderer】：Failed to Load Texture: %s\n", _texturePath.c_str());
		return;
	}

	m_material.SetTexture(pTexture);
}

// 描画用データを取得する
void MeshRenderer::GetRenderDatas(std::vector<RenderData>& _outRenderDatas) const
{
	if (!_outRenderDatas.empty())
		_outRenderDatas.clear();

	for (Mesh* pMesh : m_pMeshes)
	{
		// 描画用データを設定する
		RenderData tempData;
		{
			tempData.vertexBufferView = pMesh->GetVertexBuffer()->GetView();
			tempData.indexBufferView = pMesh->GetIndexBuffer()->GetView();
			tempData.pConstantBuffer = pMesh->GetConstantBuffer();
			tempData.indexNum = (UINT)pMesh->GetMeshData().indices.size();
			tempData.pMaterial = &m_material;
		}

		_outRenderDatas.emplace_back(tempData);
	}
}

// コンポネントデータを取得する
GameComponentData MeshRenderer::GetComponentData() const
{
	// メッシュレンダラーデータを作成する
	MeshRendererData rendererData;
	{
		rendererData.materialPath = m_material.GetFilePath();
		rendererData.meshFilePath = m_filePath;
		rendererData.textureFilePath = m_material.GetTexture()->GetFilePath();
	}

	// コンポネントデータを作成する
	GameComponentData componentData;
	{
		componentData.type = m_componentType;
		componentData.data = rendererData;
	}

	// 作成したコンポネントデータを返す
	return componentData;
}

// コンポネントを設定する
void MeshRenderer::SetComponent(const GameComponentData _componentData)
{
	MeshRendererData rendererData = _componentData.data.get<MeshRendererData>();

	ModelData modelData;
	if (Assets_I->LoadModelFile(rendererData.meshFilePath, modelData))
	{
		SetMesh(modelData);
		
		m_material.Init(rendererData.materialPath);

		m_material.SetTexture(Assets_I->GetTexture(rendererData.textureFilePath));
	}
}