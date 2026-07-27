
#include "Model.h"
using namespace Runtime;

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

	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_rotation = Quaternion::Identity();

	return true;
}

// メッシュを描画する
void Model::Draw()
{
	XMMATRIX matrix = GetTransformMatrix();
	
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

// 座標変換用の行列を取得する
XMMATRIX Model::GetTransformMatrix() const
{
	// スケーリング行列
	XMMATRIX scaleMatrix = XMMatrixScaling(
		m_scale.x,
		m_scale.y,
		m_scale.z
	);
	
	// 回転行列
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(
		DegToRad(m_rotation.x),
		DegToRad(m_rotation.y),
		DegToRad(m_rotation.z)
	);

	// 平行移動行列
	XMMATRIX translateMatrix = XMMatrixTranslation(
		m_position.x,
		m_position.y,
		m_position.z
	);

	return scaleMatrix * rotationMatrix * translateMatrix;
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

