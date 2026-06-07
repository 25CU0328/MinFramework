
#include "RenderObject.h"

// コンストラクタ
Runtime::RenderObject::RenderObject()
	: m_vertexBuffer()
	, m_indexBuffer()
	, m_constantBuffer()
{

}
// デストラクター
Runtime::RenderObject::~RenderObject()
{

}

// レンダリング用のデータを取得する
RenderData Runtime::RenderObject::GetData()
{
	return RenderData();
}

// ワールド行列を取得する
DirectX::XMMATRIX Runtime::RenderObject::GetWorldMatrix()
{
	return DirectX::XMMatrixIdentity();
}