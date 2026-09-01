#pragma once

#include "GameComponent.h"

#include "Framework/Render/RenderData.h"
#include "Transform.h"

class Renderer : public GameComponent
{
public:
	// 描画する
	virtual void Render();

	// 描画用データを取得する
	virtual void GetRenderDatas(std::vector<RenderData>& _outRenderDatas) const;

	// 描画の優先順位を設定する
	void SetRenderPriority(const int _priority);

	// 描画の優先順位を取得する
	int GetRenderPriority() const;

	// 描画処理に必要となる行列を取得する
	DirectX::XMMATRIX GetWorldMatrix() const;

private:
	// 描画の優先順位
	int m_renderPriority;
};