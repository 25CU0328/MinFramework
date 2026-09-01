
#include "CameraControlPanel.h"
#include "CameraController/CameraController_3D.h"

// 初期化処理
void CameraControlPanel::Init(const char* _panelName)
{
	ImGuiPanel::Init(_panelName);

	m_size = Vector2f(300.0f, 300.0f);

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

	// パネルの始まり
	ImGui::Begin(m_panelName);
	
	// --------------------------------------
	// カメラモードを決めるドロップボックスの設定
	// --------------------------------------
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

	// カメラの位置を取得する
	m_cameraPosition = m_pCamera->GetPosition();
	
	// カメラの回転を取得する
	Vector3f rotation = m_pCamera->GetRotationEuler();
	rotation.x = RadToDeg(rotation.x);
	rotation.y = RadToDeg(rotation.y);
	rotation.z = RadToDeg(rotation.z);
	m_cameraRotation = rotation;

	// オービット時の距離を取得する
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

	// パネルの終わり
	ImGui::End();
}

// カメラを設定する
void CameraControlPanel::SetCamera(Camera* _pCamera)
{
	m_pCamera = _pCamera;
}

// カメラのコントローラーを設定する
void CameraControlPanel::SetCameraController(CameraController_3D* const _pController)
{
	m_pCameraController = _pController;
}

// カメラのターゲットとなるモデルを追加する
void CameraControlPanel::AddTargetModel(GameObject* _pObject)
{
	// 引数はヌルポインタの場合、処理しない
	if (_pObject == nullptr || _pObject->GetName() == "")
		return;

	auto iterator = std::find(m_Objects.begin(), m_Objects.end(), _pObject);

	if (iterator != m_Objects.end())
		return;

	m_Objects.emplace_back(_pObject);

	// オービットターゲットはまだ設定されていない場合
	if (m_pOrbitObject == nullptr)
	{
		m_pOrbitObject = m_Objects.back();
	}

	// 注視ターゲットはまだ設定されていない場合
	if (m_pFocusObject == nullptr)
	{
		m_pFocusObject = m_Objects.back();
	}
}

// カメラのターゲットとなるモデルをベクターから削除する
void CameraControlPanel::RemoveTargetModel(GameObject* _pObject)
{
	// 引数はヌルポインタの場合、処理しない
	if (_pObject == nullptr)
		return;

	auto iterator = std::find(m_Objects.begin(), m_Objects.end(), _pObject);

	if (iterator != m_Objects.begin())
		return;

	// そのモデルはオービットターゲットの場合
	if (m_pOrbitObject == *iterator)
	{
		// ヌルじゃないモデルポインタを検索
		auto iterator = std::find_if_not(
			m_Objects.begin(),
			m_Objects.end(),
			[](GameObject* pObject) { return pObject == nullptr; }
		);

		// ヌルじゃないモデルポインタがあったら
		if (iterator != m_Objects.end())
		{
			m_pOrbitObject = *iterator;
		}
		// ヌルじゃないモデルポインタがない場合
		else 
		{
			m_pOrbitObject = nullptr;
		}
	}

	// そのモデルは注視ターゲットの場合
	if (m_pFocusObject == *iterator)
	{
		// ヌルじゃない
		auto iterator = std::find_if_not(
			m_Objects.begin(),
			m_Objects.end(),
			[](GameObject* pObject) { return pObject == nullptr; }
		);

		// ヌルじゃないモデルポインタがあったら
		if (iterator != m_Objects.end())
		{
			m_pFocusObject = *iterator;
		}
		// ヌルじゃないモデルポインタがない場合
		else {
			m_pFocusObject = nullptr;
		}
	}

	// ベクターから削除する
	m_Objects.erase(iterator);
}

// フリーカメラモードの内容を設定する
void CameraControlPanel::_setFreeModePanel()
{
	// 位置を調整するスライダーの設定
	ImGui::Text("位置：");
	if (ImGui::SliderFloat3("Position", &m_cameraPosition.x, -1000.0f, 1000.0f))
	{
		m_pCamera->SetPosition(m_cameraPosition);
	}

	// 回転を調整するスライダーの設定
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

	// モデルを選択するドロップボックスを設定する

	// 注視するモデルを選択するドロップボックスの設定
	ImGui::Text("モデルを注視：");
	if (ImGui::BeginCombo(
		"を",
		m_pFocusObject ?
		m_pFocusObject->GetName().c_str() : "None"
	))
	{
		for (GameObject* pObject : m_Objects)
		{
			if (pObject == nullptr)
				continue;

			bool isSelected = (m_pFocusObject == pObject);

			// モデルを選択した場合の処理
			if (ImGui::Selectable(pObject->GetName().c_str(), isSelected))
			{
				m_pFocusObject = pObject;
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}
	
	// 次のUIアイテムを同じ行で描画する命令
	ImGui::SameLine();

	// Focusボタンを設定
	if (ImGui::Button("Focus", ImVec2(50.0f, 30.0f)))
	{
		if (m_pFocusObject) 
		{
			m_pCameraController->SetLookAt(
				m_pFocusObject->GetComponent<Transform>()->GetWorldPosition()
			);
		}
	}
}

// オービットモードの内容を設定する
void CameraControlPanel::_setOrbitModePanel()
{
	// オービットのターゲットを決めるドロップボックスを設定する
	ImGui::Text("オービットターゲット：");
	if (ImGui::BeginCombo(
		"Orbit Target",
		m_pOrbitObject ? m_pOrbitObject->GetName().c_str() : "None"
	))
	{
		for (GameObject* pObject : m_Objects)
		{
			if (pObject == nullptr)
				continue;

			bool isSelected = (m_pOrbitObject == pObject);

			// モデルを選択した場合の処理
			if (ImGui::Selectable(pObject->GetName().c_str(), isSelected))
			{
				m_pOrbitObject = pObject;

				m_pCameraController->SetOrbitTarget(m_pOrbitObject);
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