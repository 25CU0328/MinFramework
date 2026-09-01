
#include "ModelControlPanel.h"

// 初期化処理
void ModelControlPanel::Init(
	const char* _panelName, 
	const Vector2f _minimunSize
)
{
	ImGuiPanel::Init(_panelName, m_minimunSize);

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
		m_modelPosition = m_pSelectedModel->GetComponent<Transform>()->GetWorldPosition();

		// 回転を取得し、角度に転換する
		Vector3f rotationEuler = m_pSelectedModel->GetComponent<Transform>()->GetLocalRotation().ToEuler();
		rotationEuler.x = RadToDeg(rotationEuler.x);
		rotationEuler.y = RadToDeg(rotationEuler.y);
		rotationEuler.z = RadToDeg(rotationEuler.z);
		m_modelRotation = rotationEuler;

		m_modelScale = m_pSelectedModel->GetComponent<Transform>()->GetLocalScale();
	}

	// 位置をコントロールするスライダーの設定
	ImGui::Text("位置");
	if (ImGui::SliderFloat3("Position:", &m_modelPosition.x, -100.0f, 100.0f) && m_pSelectedModel)
	{
		m_pSelectedModel->GetComponent<Transform>()->SetWorldPosition(m_modelPosition);
	}

	// 回転をコントロールするスライダーの設定
	ImGui::Text("回転");
	if (ImGui::SliderFloat3("Rotation:", &m_modelRotation.x, -180.0f, 180.0f) && m_pSelectedModel)
	{
		// 回転角度をラジアンに変換する
		m_modelRotation.x = DegToRad(m_modelRotation.x);
		m_modelRotation.y = DegToRad(m_modelRotation.y);
		m_modelRotation.z = DegToRad(m_modelRotation.z);

		// 回転を設定する
		m_pSelectedModel->GetComponent<Transform>()->SetLocalRotation(
			Quaternion::FromEuler(m_modelRotation)
		);
	}

	// スケールをコントロールするスライダーの設定
	ImGui::Text("スケール");
	if (ImGui::SliderFloat3("Scale:", &m_modelScale.x, 0.5, 5.0) && m_pSelectedModel)
	{
		m_pSelectedModel->GetComponent<Transform>()->SetLocalScale(m_modelScale);
	}

	ImGui::Text("操作対象");
	if (ImGui::BeginCombo(
		"モデル：",
		m_pSelectedModel ?
		m_pSelectedModel->GetName().c_str() : "None"
	))
	{
		for (GameObject* pModel : m_models)
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
}

// コントロールする対象を追加する
void ModelControlPanel::AddControlTarget(GameObject* _pModel)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), _pModel);

	if (iterator != m_models.end())
		return;

	m_models.emplace_back(_pModel);

	if (m_pSelectedModel == nullptr)
	{
		m_pSelectedModel = m_models.back();
	}
}

// コントロールする対象を記録から削除する
void ModelControlPanel::RemoveControlTarget(GameObject* _pModel)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), _pModel);

	if (iterator != m_models.begin())
		return;

	m_models.erase(iterator);
}