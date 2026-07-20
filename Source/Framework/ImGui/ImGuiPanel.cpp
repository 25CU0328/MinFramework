
#include "ImGuiPanel.h"

#include "Framework/Framework.h"

// コンストラクタ
ImGuiPanel::ImGuiPanel()
	: m_position(Vector2f(0.0f, 0.0f))
	, m_size(Vector2f(0.0f, 0.0f))
{

}

// デストラクタ
ImGuiPanel::~ImGuiPanel()
{

}

// 初期化処理
void ImGuiPanel::Init(const char* _panelName)
{
	m_panelName = _panelName;

	ImGui_I->RegistPanel(this);
}

// ImGuiアイテムを設定する
void ImGuiPanel::Render()
{
	ImGui::SetNextWindowPos(
		ImVec2(m_position.x, m_position.y)
	);

	ImGui::SetNextWindowSize(ImVec2(m_size.x, m_size.y));
}


// パネルの位置を設定する
void ImGuiPanel::SetPanelPosition(const Vector2f _position)
{
	m_position = _position;
}

// パネルの位置を取得する
Vector2f ImGuiPanel::GetPanelPosition() const
{
	return m_position;
}

// パネルのサイズを設定する
void ImGuiPanel::SetPanelSize(const Vector2f _size)
{
	m_size = _size;
}

// パネルのサイズを取得する
Vector2f ImGuiPanel::GetPanelSize() const
{
	return m_size;
}