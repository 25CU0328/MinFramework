
#include "CameraControlPanel.h"
#include "CameraController/CameraController_3D.h"

// 初期化処理
void CameraControlPanel::Init(const char* _panelName)
{
	ImGuiPanel::Init(_panelName);

	m_size = Vector2f(300.0f, 200.0f);

	m_cameraModePairs = {
		{"FreeCamera", (int)CameraMode::FreeCamera},
		{"Orbit", (int)CameraMode::Orbit}
	};

	m_selectedPair = m_cameraModePairs[0];
}

// 更新処理
void CameraControlPanel::Render()
{
	ImGuiPanel::Render();

	ImGui::Begin(m_panelName);
	
	// ------------------------
	// カメラモードのドロップボックスの設定
	// ------------------------
	ImGui::Text("カメラモード");
	if (ImGui::BeginCombo("CameraMode：",m_selectedPair.modeName.c_str()))
	{
		for (CameraModePair pair : m_cameraModePairs)
		{
			bool isSelected = (m_selectedPair == pair);

			// モデルを選択した場合の処理
			// 選択されたモードを適応し、変数に保存する
			if (ImGui::Selectable(pair.modeName.c_str(), isSelected))
			{
				m_selectedPair = pair;

				m_pCameraController->SetCameraMode(
					static_cast<CameraMode>(m_selectedPair.mode)
				);
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	m_cameraPosition = m_pCamera->GetPosition();
	Vector3f rotation = m_pCamera->GetRotationEuler();
	rotation.x = RadToDeg(rotation.x);
	rotation.y = RadToDeg(rotation.y);
	rotation.z = RadToDeg(rotation.z);
	m_cameraRotation = rotation;

	m_orbitDistance = m_pCameraController->GetOrbitDistance();

	switch (m_selectedPair.mode)
	{
	case (int)CameraMode::FreeCamera:
		_setFreeModePanel();
		break;

	case (int)CameraMode::Orbit:
		_setOrbitModePanel();
		break;
	}

	ImGui::End();
}

// カメラを設定する
void CameraControlPanel::SetCamera(Runtime::Camera* _pCamera)
{
	m_pCamera = _pCamera;
}

// カメラのコントローラーを設定する
void CameraControlPanel::SetCameraController(CameraController_3D* const _pController)
{
	m_pCameraController = _pController;
}

// Orbit時のターゲットを追加する
void CameraControlPanel::AddTargetModel(Runtime::Model* _orbitTarget)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), _orbitTarget);

	if (iterator != m_models.end())
		return;

	m_models.emplace_back(_orbitTarget);
}

// Orbit時のターゲットをベクターから削除する
void CameraControlPanel::RemoveTargetModel(Runtime::Model* _orbitTarget)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), _orbitTarget);

	if (iterator != m_models.begin())
		return;

	m_models.erase(iterator);
}

// フリーカメラモードの内容を設定する
void CameraControlPanel::_setFreeModePanel()
{
	ImGui::Text("位置：");
	if (ImGui::SliderFloat3("Position", &m_cameraPosition.x, -1000.0f, 1000.0f))
	{
		m_pCamera->SetPosition(m_cameraPosition);
	}

	ImGui::Text("回転：");
	if (ImGui::SliderFloat3("Rotation", &m_cameraRotation.x, -180.0f, 180.0f))
	{
		Vector3f rotation = {
			DegToRad(m_cameraRotation.x),
			DegToRad(m_cameraRotation.y),
			DegToRad(m_cameraRotation.z)
		};

		m_pCamera->SetRotationEuler(rotation);
	}
	ImGui::Text("モデルを注視：");
	if (ImGui::BeginCombo(
		"Model",
		m_pFocusTargetModel ?
		m_pFocusTargetModel->GetName().c_str() : "None"
	))
	{
		for (Runtime::Model* pModel : m_models)
		{
			bool isSelected = (m_pFocusTargetModel == pModel);

			// モデルを選択した場合の処理
			if (ImGui::Selectable(pModel->GetName().c_str(), isSelected))
			{
				m_pFocusTargetModel = pModel;
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}
	

	if (ImGui::Button("Focus", ImVec2(100.0f, 50.0f)))
	{
		if (m_pFocusTargetModel) 
		{
			m_pCameraController->SetLookAt(m_pFocusTargetModel->GetPosition());
		}
	}
}

// オービットモードの内容を設定する
void CameraControlPanel::_setOrbitModePanel()
{
	ImGui::Text("オービットターゲット：");
	if (ImGui::BeginCombo(
		"Orbit Target",
		m_pOrbitTargetModel ? m_pOrbitTargetModel->GetName().c_str() : "None"
	))
	{
		for (Runtime::Model* pModel : m_models)
		{
			bool isSelected = (m_pOrbitTargetModel == pModel);

			// モデルを選択した場合の処理
			if (ImGui::Selectable(pModel->GetName().c_str(), isSelected))
			{
				m_pOrbitTargetModel = pModel;

				m_pCameraController->SetOrbitTarget(m_pOrbitTargetModel);
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	// オービット距離のスライダーを設定する
	if (ImGui::SliderFloat("Orbit Distance：", &m_orbitDistance, 20.0f, 300.0f))
	{
		m_pCameraController->SetOrbitDistance(m_orbitDistance);
	}
}