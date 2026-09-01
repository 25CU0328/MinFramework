
#include "Mesh.h"


#include "DirectXMath.h"
using namespace DirectX;

#include "Framework/Framework.h"
#include <string>
// コンストラクタ
Mesh::Mesh()
{
    
}

// デストラクター
Mesh::~Mesh()
{

}

// 初期化処理
bool Mesh::Init(
    ID3D12Device* _pDevice, 
    MeshData& _data
)
{
    // バーテックスデータの初期化
    if (!m_vertexBuffer.Init(
        _pDevice,
        _data.vertexDatas.size(),
        sizeof(VertexData),
        _data.vertexDatas.data())
    )
    {
        printf("【Mesh】：Failed to Init VertexBuffer\n");
        return false;
    }

    // インデックスバッファーの初期化
    if (!m_indexBuffer.Init(
        _pDevice,
        (UINT)_data.indices.size(),
        (UINT)sizeof(uint32_t),
        _data.indices.data())
        )
    {
        printf("【Mesh】：Failed to Init IndicesBuffer\n");
        return false;
    }

    // 定数バッファーの初期化
    if (!m_constantBuffer.Init(_pDevice))
    {
        printf("【Mesh】：Failed to Init ConstantBuffer\n");
        return false;
    }
   
    m_meshData = _data;
    return true;
}


// ヴァーテックスバッファーを取得する
const Render::VertexBuffer* Mesh::GetVertexBuffer() const
{
    return &m_vertexBuffer;
}

// インデックスバッファーを取得する
const Render::IndexBuffer* Mesh::GetIndexBuffer() const
{
    return &m_indexBuffer;
}

// 定数バッファーを取得する
const Render::ConstantBuffer* Mesh::GetConstantBuffer() const
{
    return &m_constantBuffer;
}

// メッシュを取得する
MeshData Mesh::GetMeshData() const
{
    return m_meshData;
}
