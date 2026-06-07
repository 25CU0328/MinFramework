#pragma once

#include "Render/Resource/VertexBuffer.h"
#include "Render/Resource/IndexBuffer.h"
#include "Render/Resource/ConstantBuffer.h"
#include "Render/RenderData.h"

#include <DirectXMath.h>

namespace Runtime
{
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
		// ワールド行列を取得する
		virtual DirectX::XMMATRIX GetWorldMatrix();
	protected:
		

		// ---------------------------
		// バッファー
		// ---------------------------
		Render::VertexBuffer	m_vertexBuffer;		// ヴァーテックスバッファー
		Render::IndexBuffer		m_indexBuffer;		// インデックスバッファー
		Render::ConstantBuffer	m_constantBuffer;	// 定数バッファー

		Runtime::Material		m_material;			// マテリアル
	};
}