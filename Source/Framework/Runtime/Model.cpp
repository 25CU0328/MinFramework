
#include "Model.h"
using namespace Runtime;

#include "Framework/Framework.h"

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
	// モデルが持つメッシュを描画する
	for (Mesh* pMesh : m_pMeshes)
	{
		pMesh->Draw();
	}
}