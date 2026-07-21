
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
	if (ImGui::BeginCombo(
		"CameraMode：",
		m_selectedPair.modeName.c_str()
	))
	{
		for (CameraModePair pair : m_cameraModePairs)
		{
			bool isSelected = (m_selectedPair == pair);

			// モデルを選択した場合の処理
			if (ImGui::Selectable(pair.modeName.c_str(), isSelected))
			{
				m_selectedPair = pair;

				m_pCameraController->SetCameraMode(static_cast<CameraMode>(m_selectedPair.mode));
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	m_cameraPosition = m_pCamera->GetPosition();
	m_cameraRotation = m_pCamera->GetRotation();
	m_orbitDistance = m_pCameraController->GetOrbitDistance();

	if (m_selectedPair.mode == (int)CameraMode::FreeCamera) {
		ImGui::Text("位置");
		if (ImGui::SliderFloat3("Position:", &m_cameraPosition.x, -1000.0f, 1000.0f))
		{
			m_pCamera->SetPosition(m_cameraPosition);
		}

		ImGui::Text("回転");
		if (ImGui::SliderFloat3("Rotation:", &m_cameraRotation.x, 0.0f, 360.0f))
		{
			Vector3f rotation = {
				DegToRad(m_cameraRotation.x),
				DegToRad(m_cameraRotation.y),
				DegToRad(m_cameraRotation.z)
			};

			m_pCamera->SetRotation(rotation);
		}
	}
	else if (m_selectedPair.mode == (int)CameraMode::Orbit)
	{
		// -------------------------------
		// 
		// -------------------------------
		ImGui::Text("オービット ターゲット：");
		if (ImGui::BeginCombo(
			"Orbit Target",
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

					m_pCameraController->SetOrbitTarget(m_pSelectedModel);
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
void CameraControlPanel::AddOrbitTarget(Runtime::Model* _orbitTarget)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), _orbitTarget);

	if (iterator != m_models.end())
		return;

	m_models.emplace_back(_orbitTarget);
}

// Orbit時のターゲットをベクターから削除する
void CameraControlPanel::RemoveOrbitTarget(Runtime::Model* _orbitTarget)
{
	auto iterator = std::find(m_models.begin(), m_models.end(), _orbitTarget);

	if (iterator != m_models.begin())
		return;

	m_models.erase(iterator);
}
