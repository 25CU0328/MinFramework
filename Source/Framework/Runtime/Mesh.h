#pragma once

#include "Framework/Assets/Model/ModelData.h"

#include "Framework/Render/Resource/VertexBuffer.h"
#include "Framework/Render/Resource/IndexBuffer.h"
#include "Framework/Render/Resource/ConstantBuffer.h"


// モデルのメッシュを表すクラス
class Mesh
{
public:
	// コンストラクタ
	Mesh();
	// デストラクター
	~Mesh();

public:
	// 初期化処理
	bool Init(
		ID3D12Device* _pDevice, 
		MeshData& _data
	);


	// ヴァーテックスバッファーを取得する
	const Render::VertexBuffer* GetVertexBuffer() const;
	// インデックスバッファーを取得する
	const Render::IndexBuffer* GetIndexBuffer() const;
	// 定数バッファーを取得する
	const Render::ConstantBuffer* GetConstantBuffer() const;
	
	// メッシュを取得する
	MeshData GetMeshData() const;

private:
	// ---------------------------
	// バッファー
	// ---------------------------
	Render::VertexBuffer	m_vertexBuffer;		// ヴァーテックスバッファー
	Render::IndexBuffer		m_indexBuffer;		// インデックスバッファー
	Render::ConstantBuffer	m_constantBuffer;	// 定数バッファー

	int m_renderPriority;	// 描画の優先順位

	MeshData m_meshData;	// メッシュを生成する時に使われるデータ
};

