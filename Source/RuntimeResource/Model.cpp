
#include "Model.h"
using namespace Runtime;

#include "Framework.h"

// 初期化処理
bool Model::Init(ModelData _data)
{
	// レンダリングマネージャーから
	// デバイスを取得する
	ID3D12Device* pDevice = Render_I->GetDevice();

	for (MeshData meshData : _data.meshDatas)
	{
		m_pMeshes.emplace_back(new Mesh());

		if (!m_pMeshes.back()->Init(pDevice, meshData))
		{
			return false;
		}
	}

	return true;
}

// メッシュを描画する
void Model::Draw(Camera* _pCamera)
{
	// レンダリングマネージャーから
	// コマンドリストを取得する
	ID3D12GraphicsCommandList* pCommandList = Render_I->GetCommandList();

	for (Mesh* pMesh : m_pMeshes)
	{
		pMesh->Draw(pCommandList, _pCamera);
	}
}