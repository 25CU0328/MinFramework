
#include "RenderObject.h"

// コンストラクタ
Runtime::RenderObject::RenderObject()
	: m_vertexBuffer()
	, m_indexBuffer()
	, m_constantBuffer()
	, m_renderPriority(INT_MAX)
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
DirectX::XMMATRIX Runtime::RenderObject::GetTransformMatrix() const
{
	return DirectX::XMMatrixIdentity();
}


// 描画の優先順位を設定する
void Runtime::RenderObject::SetRenderPriority(const int _priority)
{
	m_renderPriority = _priority;
}

// 描画の優先順位を取得する
int Runtime::RenderObject::GetRenderPriority() const
{
	return m_renderPriority;
}