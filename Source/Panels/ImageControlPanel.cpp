
#include "ImageControlPanel.h"

// 初期化処理
void ImageControlPanel::Init(const char* _panelName, Runtime::Sprite* _targetSprite)
{
	ImGuiPanel::Init(_panelName);

	m_pSprite = _targetSprite;
	m_size = m_pSprite->GetSize();
	m_position = m_pSprite->GetPosition();
}

// 描画処理
void ImageControlPanel::Render()
{
	ImGui::SetNextWindowPos(ImVec2(100.0f, 100.0f), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500.0f, 300.0f));
	ImGui::Begin(m_panelName);
	ImGui::Text("位置");
	ImGui::SliderFloat2("Position:", &m_position.x, -100.0f, 100.0f);

	ImGui::Text("サイズ");
	ImGui::SliderFloat2("Size:", &m_size.x, 20.0f, 80.0f);
	ImGui::End();



	m_pSprite->SetPosition(m_position);
	m_pSprite->SetSize(m_size);
}