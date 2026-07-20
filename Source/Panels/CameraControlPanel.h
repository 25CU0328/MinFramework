#pragma once

#include "Framework/ImGui/ImGuiPanel.h"

#include "Framework/Runtime/Camera.h"
//#include "CameraController/CameraController_3D.h"

class CameraControlPanel : public ImGuiPanel
{
public:
	// 初期化処理
	void Init(const char* _panelName = "");

	// 描画処理
	void Render();

	// カメラを設定する
	void SetCamera(Runtime::Camera* _pCamera);


private:
	// カメラの位置
	Vector3f m_cameraPosition;
	// カメラの回転
	Vector3f m_cameraRotation;

	// カメラ
	Runtime::Camera* m_pCamera;
	// カメラのコントローラー
	//CameraController_3D* m_pCameraController;
};