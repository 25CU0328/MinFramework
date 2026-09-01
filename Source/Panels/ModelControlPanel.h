
#pragma once

#include "Framework/ImGui/ImGuiPanel.h"

#include "Framework/Runtime/GameObject.h"


#include <vector>

class ModelControlPanel : public ImGuiPanel
{
public:
	// 初期化処理
	void Init(
		const char* _panelName = "", 
		const Vector2f _minimunSize = Vector2f(100.0f, 100.0f)
	);

	// 描画処理
	void Render();

	// コントロールする対象を追加する
	void AddControlTarget(GameObject* _pModel);
	// コントロールする対象を記録から削除する
	void RemoveControlTarget(GameObject* _pModel);

private:
	// モデルの位置
	Vector3f m_modelPosition;
	// モデルのスケール
	Vector3f m_modelScale;
	// モデルの回転
	Vector3f m_modelRotation;

	// 選択されたモデル
	GameObject* m_pSelectedModel;
	// コントロール対象となるモデル
	std::vector<GameObject*> m_models;
};