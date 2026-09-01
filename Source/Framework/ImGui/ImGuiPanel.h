#pragma once

#include "imgui.h"
#include <string>
#include "Framework/Math/Vector2.h"

// ImGuiPanelを管理するマネージャークラス
class ImGuiManager;

// 
class ImGuiPanel
{
public:
	// コンストラクタ
	ImGuiPanel();
	// デストラクタ
	~ImGuiPanel();
	// 初期化処理
	virtual void Init(
		const char* _panelName,
		const Vector2f _minimunSize = Vector2f(100.0f, 100.0f)
	);

	// ImGuiアイテムを設定する
	virtual void Render();

	// パネルの位置を設定する
	void SetPanelPosition(const Vector2f _position);
	// パネルの位置を取得する
	Vector2f GetPanelPosition() const;

	// パネルのサイズを設定する
	void SetPanelSize(const Vector2f _size);
	// 最小サイズを設定する
	void SetMinimunSize(const Vector2f _size);
	// パネルのサイズを取得する
	Vector2f GetPanelSize() const;

	// パネルを表示するかを設定する
	void SetPanelDisplay(const bool _display);

protected :
	// パネルの位置
	Vector2f m_position;
	// パネルのサイズ
	Vector2f m_size;
	// パネルの最小サイズ
	Vector2f m_minimunSize;

	// パネル名
	const char* m_panelName;

private:
	// サイズ・位置情報が更新されたかのフラグ
	bool m_isDirty;

	// パネルを表示するかのフラグ
	bool m_isDisplay;
};
