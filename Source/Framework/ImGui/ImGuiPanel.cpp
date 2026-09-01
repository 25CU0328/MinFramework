
#include "ImGuiPanel.h"

#include "Framework/Framework.h"

// コンストラクタ
ImGuiPanel::ImGuiPanel()
	: m_position(Vector2f(0.0f, 0.0f))
	, m_size(Vector2f(0.0f, 0.0f))
	, m_minimunSize(Vector2f(0.0f, 0.0f))
	, m_isDirty(false)
	, m_isDisplay(true)
{

}

// デストラクタ
ImGuiPanel::~ImGuiPanel()
{

}

// 初期化処理
void ImGuiPanel::Init(const char* _panelName, const Vector2f _minimunSize)
{
	// パネル名を設定する
	m_panelName = _panelName;

	// 最小サイズを設定する
	m_minimunSize = _minimunSize;

	// マネージャーに登録する
	ImGui_I->RegistPanel(this);
}

// ImGuiアイテムを設定する
void ImGuiPanel::Render()
{
	// 表示しないと設定されたら、処理しない
	if (!m_isDisplay)
		return;

	// 更新が必要な場合
	if (m_isDirty)
	{
		// パネル位置を設定する
		ImGui::SetNextWindowPos(
			ImVec2(m_position.x, m_position.y)
		);

		// パネルサイズを設定する
		ImGui::SetNextWindowSize(ImVec2(m_size.x, m_size.y));
	}
}


// パネルの位置を設定する
void ImGuiPanel::SetPanelPosition(const Vector2f _position)
{
	m_position = _position;

	m_isDirty = true;
}

// パネルの位置を取得する
Vector2f ImGuiPanel::GetPanelPosition() const
{
	return m_position;
}

// パネルのサイズを設定する
void ImGuiPanel::SetPanelSize(const Vector2f _size)
{
	m_size.x = std::max<float>(_size.x, m_minimunSize.x);
	m_size.y = std::max<float>(_size.y, m_minimunSize.y);

	m_isDirty = true;
}

// 最小サイズを設定する
void ImGuiPanel::SetMinimunSize(const Vector2f _size)
{
	m_minimunSize = _size;
}

// パネルのサイズを取得する
Vector2f ImGuiPanel::GetPanelSize() const
{
	return m_size;
}

// パネルを表示するかを設定する
void ImGuiPanel::SetPanelDisplay(const bool _isDisplay)
{
	m_isDisplay = _isDisplay;
}