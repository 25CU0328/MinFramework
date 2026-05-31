#pragma once

#include "Assets/Model/ModelData.h"
#include "Render/Resource/VertexBuffer.h"
#include "Render/Resource/IndexBuffer.h"
#include "Render/Resource/ConstantBuffer.h"

#include "Camera.h"

namespace Runtime
{
	class Mesh
	{
	public:
		// コンストラクタ
		Mesh();
		// デストラクター
		~Mesh();

		// 初期化処理
		bool Init(ID3D12Device* _pDevice, MeshData& _data);

		// メッシュを描画する
		void Draw(ID3D12GraphicsCommandList* _pCommandList, Camera* _pCamera);

		// ワールド座標を取得する
		XMMATRIX GetWorldMatrix() const;
	private:
		MeshData m_data;

		// ---------------------------
		// バッファー
		// ---------------------------
		Render::VertexBuffer m_vertexBuffer;
		Render::IndexBuffer  m_indexBuffer;
		Render::ConstantBuffer m_constantBuffer;

		XMFLOAT3 m_position;	// 位置
		XMFLOAT3 m_rotation;	// 回転角度
		XMFLOAT3 m_scale;		// サイズスケイル
	};
}