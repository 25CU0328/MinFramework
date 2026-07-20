
#include "Mesh.h"
using namespace Runtime;

#include "DirectXMath.h"
using namespace DirectX;

#include "Framework/Framework.h"
#include <string>
// コンストラクタ
Mesh::Mesh()
    : m_position(0, 0, 0)
    , m_rotation(0, 0, 0)
    , m_scale(1, 1, 1)
{
    
}

// デストラクター
Mesh::~Mesh()
{

}

// 初期化処理
bool Mesh::Init(
    ID3D12Device* _pDevice, 
    MeshData& _data,
    std::string _materialName
)
{
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

    if (!m_constantBuffer.Init(_pDevice))
    {
        return false;
    }

   
    // メッシュデータを受け取る
    m_meshData = _data;

    _materialName = _materialName == ""
        ? "Assets/Materials/SpriteDefaultMaterial.txt"
        : _materialName;

    if (!m_material.Init(_materialName))
    {
        printf("【Mesh】：Failed to Init Material\n");
        return false;
    }
   

    return true;
}

// メッシュを描画する命令
void Mesh::Draw()
{
    Render_I->QueueRender(this);
}

// 座標変換用の行列を設定する
void Mesh::SetTransformMatrix(const XMMATRIX _matrix)
{
    m_transformMatrix = _matrix;
}

// 座標変換用の行列を取得する
XMMATRIX Mesh::GetTransformMatrix() const
{
    return m_transformMatrix;
}

// レンダリング用のデータを取得する
RenderData Mesh::GetData()
{
    RenderData renderData = {};
    renderData.vertexBufferView = m_vertexBuffer.GetView();
    renderData.indexBufferView = m_indexBuffer.GetView();
    renderData.pConstantBuffer = &m_constantBuffer;
    renderData.indexNum = (UINT)m_meshData.indices.size();
    renderData.pMaterial = &m_material;

    return renderData;
}