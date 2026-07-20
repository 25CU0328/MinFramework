
#include "ImageControlPanel.h"

// 初期化処理
void ImageControlPanel::Init(const char* _panelName, Runtime::Sprite* _targetSprite)
{
	ImGuiPanel::Init(_panelName);

	m_pSprite = _targetSprite;
	m_spriteSize = m_pSprite->GetSize();
	m_spritePosition = m_pSprite->GetPosition();


	m_position = Vector2f(0.0f, 0.0f);
	m_size = Vector2f(400.0f, 250.0f);
}

// 描画処理
void ImageControlPanel::Render()
{
	ImGuiPanel::Render();

	ImGui::Begin(m_panelName);
	ImGui::Text("位置");
	ImGui::SliderFloat2("Position:", &m_spritePosition.x, -300.0f, 300.0f);
	
	ImGui::Text("回転");
	ImGui::SliderInt("Rotation:", &m_spriteRotation, 0, 360);

	ImGui::Text("サイズ");
	ImGui::SliderFloat2("Size:", &m_spriteSize.x, 80.0f, 200.0f);
	ImGui::End();



	m_pSprite->SetPosition(m_spritePosition);
	m_pSprite->SetSize(m_spriteSize);
	m_pSprite->SetRotation(m_spriteRotation);
}