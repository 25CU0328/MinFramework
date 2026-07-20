#pragma once

#include "imgui.h"
#include <string>
#include "Framework/Math/Vector2.h"

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

	// パネルの位置を設定する
	void SetPanelPosition(const Vector2f _position);
	// パネルの位置を取得する
	Vector2f GetPanelPosition() const;
	// パネルのサイズを設定する
	void SetPanelSize(const Vector2f _size);
	// パネルのサイズを取得する
	Vector2f GetPanelSize() const;
protected :
	// パネルの位置
	Vector2f m_position;
	// パネルのサイズ
	Vector2f m_size;

	// パネル名
	const char* m_panelName;
};
