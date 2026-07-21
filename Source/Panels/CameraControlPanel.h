#pragma once

#include "Framework/ImGui/ImGuiPanel.h"

#include "Framework/Runtime/Model.h"
#include "Framework/Runtime/Camera.h"

#include <vector>

class CameraController_3D;

class CameraControlPanel : public ImGuiPanel
{
public:
	// 初期化処理
	void Init(const char* _panelName = "");

	// 描画処理
	void Render();

	// カメラを設定する
	void SetCamera(Runtime::Camera* _pCamera);

	// カメラのコントローラーを設定する
	void SetCameraController(CameraController_3D* _pController);

	// Orbit時のターゲットを追加する
	void AddOrbitTarget(Runtime::Model* _orbitTarget);
	// Orbit時のターゲットをベクターから削除する
	void RemoveOrbitTarget(Runtime::Model* _orbitTarget);
private:
	// カメラの位置
	Vector3f m_cameraPosition;
	// カメラの回転
	Vector3f m_cameraRotation;

	// カメラ
	Runtime::Camera* m_pCamera;
	// カメラのコントローラー
	CameraController_3D* m_pCameraController;

	// ---------------------------
	// カメラモードを記録するプロパティ
	// ---------------------------
private:
	// カメラモードとそのモードを表す文字列
	struct CameraModePair
	{
		bool operator==(const CameraModePair& _otherPair)
		{
			return (modeName == _otherPair.modeName) && (mode == _otherPair.mode);
		}

		std::string modeName;
		int mode;
	};
	std::vector<CameraModePair> m_cameraModePairs;
	// 選択されたペア
	CameraModePair m_selectedPair;

	// -----------------------------
	// Orbit Modeに使われるプロパティ
	// -----------------------------
private:
	float m_orbitDistance;

	// 選択されたモデル
	Runtime::Model* m_pSelectedModel;
	// コントロール対象となるモデル
	std::vector<Runtime::Model*> m_models;
};