#pragma once

#include "imgui.h"
#include <string>

class ImGuiManager;
class ImGuiPanel
{
public:
	// コンストラクタ
	ImGuiPanel();
	// デストラクタ
	~ImGuiPanel();
	// 初期化処理
	virtual void Init(const char* _penalName);
	// ImGuiアイテムを設定する
	virtual void Render();
protected :
	const char* m_panelName;
};
