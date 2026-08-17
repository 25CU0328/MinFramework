#pragma once

#include "Framework/Render/Resource/VertexBuffer.h"
#include "Framework/Render/Resource/IndexBuffer.h"
#include "Framework/Render/Resource/ConstantBuffer.h"
#include "Framework/Render/RenderData.h"

#include <DirectXMath.h>

class RenderObject
{
	// コピーを禁止する
	RenderObject(const RenderObject&) = delete;
	// オペレーターによるコピーを禁止する
	void operator = (const RenderObject&) = delete;
public:
	// コンストラクタ
	RenderObject();
	// デストラクター
	~RenderObject();

	// レンダリング用のデータを取得する
	virtual RenderData GetData();
	// 変換行列を取得する
	virtual DirectX::XMMATRIX GetTransformMatrix() const;

	// 描画の優先順位を設定する
	void SetRenderPriority(const int _priority);
	// 描画の優先順位を取得する
	int GetRenderPriority() const;
protected:
	// ---------------------------
	// バッファー
	// ---------------------------
	Render::VertexBuffer	m_vertexBuffer;		// ヴァーテックスバッファー
	Render::IndexBuffer		m_indexBuffer;		// インデックスバッファー
	Render::ConstantBuffer	m_constantBuffer;	// 定数バッファー

	Runtime::Material		m_material;			// マテリアル

private:

	int m_renderPriority;	// 描画の優先順位
};
