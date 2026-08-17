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
	void SetCamera(Camera* _pCamera);

	// カメラのコントローラーを設定する
	void SetCameraController(CameraController_3D* _pController);

	// カメラのターゲットとなるモデルを追加する
	void AddTargetModel(Model* _orbitTarget);
	// カメラのターゲットとなるモデルをベクターから削除する
	void RemoveTargetModel(Model* _orbitTarget);

private:
	// フリーカメラモードの内容を設定する
	void _setFreeModePanel();
	// オービットモードの内容を設定する
	void _setOrbitModePanel();
	

private:
	// カメラの位置
	Vector3f m_cameraPosition;
	// カメラの回転
	Vector3f m_cameraRotation;

	// カメラ
	Camera* m_pCamera;
	// カメラのコントローラー
	CameraController_3D* m_pCameraController;

	// 注視する目標となるモデル
	Model* m_pFocusTargetModel;

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

	// オービットターゲットとなるモデル
	Model* m_pOrbitTargetModel;
	// コントロール対象となるモデル
	std::vector<Model*> m_models;
};