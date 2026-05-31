
#include "Mesh.h"
using namespace Runtime;

#include "DirectXMath.h"
using namespace DirectX;


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
bool Mesh::Init(ID3D12Device* _pDevice, MeshData& _data)
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
        _data.indices.size(),
        sizeof(uint32_t),
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

    m_data = _data;

    return true;
}

// メッシュを描画する命令
void Mesh::Draw(ID3D12GraphicsCommandList* _pCommandList, Camera* _pCamera)
{
    _pCommandList->SetGraphicsRootConstantBufferView(
        1, // rootParameterと同じ(良くないMagic Number)
        m_constantBuffer.GetResource()->GetGPUVirtualAddress()
    );

    // 行列計算
    {
        XMMATRIX matrix = GetWorldMatrix() * _pCamera->GetViewProjectionMatrix();

        // objとDirectXの座標系が異なるための処理
        matrix = XMMatrixTranspose(matrix);
        m_constantBuffer.UpdateMatrix(&matrix, sizeof(matrix));
    }

    _pCommandList->IASetVertexBuffers(0, 1, &m_vertexBuffer.GetView());
    _pCommandList->IASetIndexBuffer(&m_indexBuffer.GetView());
    _pCommandList->DrawIndexedInstanced(
        m_data.indices.size(),
        1,
        0,
        0,
        0
    );


}

// ワールド座標を取得する
XMMATRIX Mesh::GetWorldMatrix() const
{
    XMMATRIX scaleMatrix =XMMatrixScaling(
        m_scale.x,
        m_scale.y,
        m_scale.z
    );

    XMMATRIX rotationMatrix =XMMatrixRotationRollPitchYaw(
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