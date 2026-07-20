
#include "CameraControlPanel.h"

// 初期化処理
void CameraControlPanel::Init(const char* _panelName)
{
	ImGuiPanel::Init(_panelName);

	m_size = Vector2f(300.0f, 200.0f);
}

// 更新処理
void CameraControlPanel::Render()
{
	ImGuiPanel::Render();

	ImGui::Begin(m_panelName);

	m_cameraPosition = m_pCamera->GetPosition();
	m_cameraRotation = m_pCamera->GetRotation();

	ImGui::Text("位置");
	if (ImGui::SliderFloat3("Position:", &m_cameraPosition.x, -1000.0f, 1000.0f))
	{
		m_pCamera->SetPosition(m_cameraPosition);
	}

	ImGui::Text("回転");
	if (ImGui::SliderFloat3("Rotation:", &m_cameraRotation.x, 0.0f, 360.0f))
	{
		m_cameraRotation.x = DegToRad(m_cameraRotation.x);
		m_cameraRotation.y = DegToRad(m_cameraRotation.y);
		m_cameraRotation.z = DegToRad(m_cameraRotation.z);
		m_pCamera->SetRotation(m_cameraRotation);
	}

	if (ImGui::BeginCombo("カメラモード：", "")) {



		ImGui::EndCombo();
	}
	
	ImGui::End();
}

// カメラを設定する
void CameraControlPanel::SetCamera(Runtime::Camera* _pCamera)
{
	m_pCamera = _pCamera;
}
