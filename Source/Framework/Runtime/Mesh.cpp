
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

// ワールド座標を取得する
XMMATRIX Mesh::GetWorldMatrix() const
{
    XMMATRIX scaleMatrix =XMMatrixScaling(
        m_scale.x,
        m_scale.y,
        m_scale.z
    );

    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x,
        m_rotation.y,
        m_rotation.z
    );

    XMMATRIX translateMatrix = XMMatrixTranslation(
        m_position.x,
        m_position.y,
        m_position.z
    );

    return scaleMatrix * rotationMatrix * translateMatrix;
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