
#include "ImGuiPanel.h"

#include "Framework/Framework.h"

// コンストラクタ
ImGuiPanel::ImGuiPanel()
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
	// 子供クラスから記述する
}