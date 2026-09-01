
#include "Renderer.h"
#include "Framework/Runtime/GameObject.h"

// 描画する
void Renderer::Render()
{

}
// 描画用データを取得する
void Renderer::GetRenderDatas(std::vector<RenderData>& _outRenderDatas) const
{

}


// 描画の優先順位を設定する
void Renderer::SetRenderPriority(const int _priority)
{
	m_renderPriority = _priority;
}

// 描画の優先順位を取得する
int Renderer::GetRenderPriority() const
{
	return m_renderPriority;
}

// 描画処理に必要となる行列を取得する
DirectX::XMMATRIX Renderer::GetWorldMatrix() const
{
	return m_pOwnerObject->GetComponent<Transform>()->GetWorldMatrix();
}