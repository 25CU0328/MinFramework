#pragma once

#include "Framework/Assets/Model/ModelData.h"
#include "RenderObject.h"
#include "Framework/Math/Vector3.h"

#include "Camera.h"


class Mesh : public RenderObject
{
public:
	// コンストラクタ
	Mesh();
	// デストラクター
	~Mesh();

	// 初期化処理
	bool Init(
		ID3D12Device* _pDevice, 
		MeshData& _data, 
		std::string _materialName = ""
	);

	// メッシュを描画する
	void Draw();

	// 座標変換用の行列を設定する
	void SetTransformMatrix(const XMMATRIX _matrix);
	// 座標変換用の行列を取得する
	XMMATRIX GetTransformMatrix() const;

	// レンダリング用のデータを取得する
	RenderData GetData();

	// テクスチャを設定する
	void SetTexture(Render::Texture* const _pTexture);
private:
	MeshData m_meshData;

	Vector3f m_position;	// 位置
	Vector3f m_rotation;	// 回転角度
	Vector3f m_scale;		// スケール

	XMMATRIX m_transformMatrix;		// 座標変換用の行列
};
