#pragma once

#include "Mesh.h"
#include "Framework/Assets/Model/ModelData.h"
#include "GameObject.h"

class Model : public GameObject
{
public:

	// 初期化処理
	bool Init(
		ModelData _data, 
		std::string _materialName = ""
	);

	// メッシュを描画する
	void Draw();

	// テクスチャを設定する
	void SetTexture(Render::Texture* const _pTexture);

	// 描画の優先順位を設定する
	void SetRenderPriority(const int _priority);
	// 描画の優先順位を取得する
	int GetRenderPriority() const;

private:
	// モデルにある全てのメッシュ
	std::vector<Mesh*> m_pMeshes;

	int m_renderPriority;	// 描画の優先順位
};
