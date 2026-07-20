
#include "ModelControlPanel.h"

// 初期化処理
void ModelControlPanel::Init(const char* _panelName)
{
	ImGuiPanel::Init(_panelName);

	m_size = Vector2f(300.0f, 300.0f);

	m_modelPosition = Vector3f(0.0f, 0.0f, 0.0f);
	m_modelRotation = Vector3f(0.0f, 0.0f, 0.0f);
	m_modelScale = Vector3f(0.0f, 0.0f, 0.0f);
}

// 描画処理
void ModelControlPanel::Render()
{
	ImGuiPanel::Render();
	 
	ImGui::Begin(m_panelName);
	
	// 選択されたモデルがある場合
	if (m_pSelectedModel)
	{
		m_modelPosition = m_pSelectedModel->GetPosition();
		m_modelRotation = m_pSelectedModel->GetRotation();
		m_modelScale = m_pSelectedModel->GetScale();
	}

	ImGui::Text("位置");
	if(ImGui::SliderFloat3("Position:", &m_modelPosition.x, -100.0f, 100.0f) && m_pSelectedModel)
	{
		m_pSelectedModel->SetPosition(m_modelPosition);
	}

	ImGui::Text("回転");
	if (ImGui::SliderFloat3("Rotation:", &m_modelRotation.x, 0.0f, 360.0f) && m_pSelectedModel)
	{
		m_pSelectedModel->SetRotation(m_modelRotation);
	}

	ImGui::Text("スケール");
	if (ImGui::SliderFloat3("Scale:", &m_modelScale.x, 0.5, 5.0) && m_pSelectedModel)
	{
		m_pSelectedModel->SetScale(m_modelScale);
	}

	ImGui::Text("操作対象");
	if (ImGui::BeginCombo(
		"モデル：",
		m_pSelectedModel ? 
		m_pSelectedModel->GetName().c_str() : "None"
	))
	{
		for (Runtime::Model* pModel : m_models)
		{
			bool isSelected = (m_pSelectedModel == pModel);

			// モデルを選択した場合の処理
			if (ImGui::Selectable(pModel->GetName().c_str(), isSelected))
			{
				m_pSelectedModel = pModel;
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}
	ImGui::End();

	if (m_pSelectedModel){
		
		
		
	}
}

// コントロールする対象を追加する
void ModelControlPanel::AddControlTarget(Runtime::Model* _pModel)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), m_pModel);

	if (iterator != m_models.end())
		return;

	m_models.emplace_back(_pModel);
}

// コントロールする対象を記録から削除する
void ModelControlPanel::RemoveControlTarget(Runtime::Model* _pModel)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), m_pModel);

	if (iterator != m_models.begin())
		return;

	m_models.erase(iterator);
}