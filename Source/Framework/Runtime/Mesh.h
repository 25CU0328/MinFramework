#pragma once

#include "Assets/Model/ModelData.h"
#include "RenderObject.h"
#include "Math/Vector3.h"

#include "Camera.h"

namespace Runtime
{
	class Mesh : RenderObject
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

		// ワールド行列を取得する
		XMMATRIX GetWorldMatrix() const;

		// レンダリング用のデータを取得する
		RenderData GetData();
	private:
		MeshData m_meshData;

		Vector3f m_position;	// 位置
		Vector3f m_rotation;	// 回転角度
		Vector3f m_scale;		// サイズスケイル
	};
}