
#pragma once

#include "Framework/ImGui/ImGuiPanel.h"

#include "ImageControlPanel.h"
#include "Framework/Runtime/Model.h"

#include <vector>

class ModelControlPanel : public ImGuiPanel
{
public:
	// 初期化処理
	void Init(const char* _panelName = "");

	// 描画処理
	void Render();

	// コントロールする対象を追加する
	void AddControlTarget(Runtime::Model* _pModel);
	// コントロールする対象を記録から削除する
	void RemoveControlTarget(Runtime::Model* _pModel);

private:
	// モデルの位置
	Vector3f m_modelPosition;
	// モデルのスケール
	Vector3f m_modelScale;
	// モデルの回転
	Vector3f m_modelRotation;

	
	Runtime::Model* m_pModel;

	Runtime::Model* m_pSelectedModel;
	// コントロール対象となるモデル
	std::vector<Runtime::Model*> m_models;
};