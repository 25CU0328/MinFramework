
#include "Model.h"

#include "Framework/Framework.h"
#include "Framework/Math/Math.h"
// 初期化処理
bool Model::Init(
	ModelData _data,
	std::string _materialName
)
{
	// レンダリングマネージャーから
	// デバイスを取得する
	ID3D12Device* pDevice = Render_I->GetGraphics()->GetDevice();

	for (MeshData meshData : _data.meshDatas)
	{
		m_pMeshes.emplace_back(new Mesh());

		if (!m_pMeshes.back()->Init(pDevice, meshData, _materialName))
		{
			return false;
		}
	}

	return true;
}

// メッシュを描画する
void Model::Draw()
{
	XMMATRIX matrix = GetTransform().GetWorldMatrix();
	
	for (Mesh* pMesh : m_pMeshes)
	{
		// 行列を設定する
		pMesh->SetTransformMatrix(matrix);
		
		// メッシュを描画する
		pMesh->Draw();
	}
}

// テクスチャを設定する
void Model::SetTexture(Render::Texture* const _pTexture)
{
	for (Mesh* pMesh : m_pMeshes)
	{
		pMesh->SetTexture(_pTexture);
	}
}

// 描画の優先順位を設定する
void Model::SetRenderPriority(const int _priority)
{
	m_renderPriority = _priority;

	for (Mesh* pMesh : m_pMeshes)
	{
		pMesh->SetRenderPriority(m_renderPriority);
	}
}

// 描画の優先順位を取得する
int Model::GetRenderPriority() const
{
	return m_renderPriority;
}

