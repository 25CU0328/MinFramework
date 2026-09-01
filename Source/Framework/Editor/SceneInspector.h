#pragma once

#include "EditorDef.h"

#ifdef EDITOR_DEF

#include "Framework/ImGui/ImGuiPanel.h"
#include "Framework/Scene/Scene.h"

class SceneInspector : ImGuiPanel
{
public:
	// 初期化処理
	void Init(const char* _panelName, const Vector2f _minimunSize);
	
	// 描画処理
	void Render();

private:
	// ドラッグ&ドロップ処理
	void _dragDrop();

	// ゲームオブジェクトを表示する
	void _drawNode(GameObject* _pGameObejct);

private:
	// パネルに表示するシーン
	Scene* m_pScene;

	// 選択されたオブジェクト
	GameObject* m_pSelectedObject;

	// ドラッグされたオブジェクト
	GameObject* m_pDragObject;
};

#endif // EDITOR_DEF