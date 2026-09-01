
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework/Framework.h"

#include "AppDef.h"

#include "Framework/Runtime/Camera.h"
#include "Framework/Assets/AssetData/MaterialData.h"
#include "Panels/ModelControlPanel.h"
#include "Panels/CameraControlPanel.h"
#include "CameraController/CameraController_3D.h"

#include "Framework/Scene/Scene.h"
#include "Framework/Runtime/Component/GameComponents.h"

Camera camera;

GameObject cubeObject;

// モデルの操作パネル
ModelControlPanel modelControlPanel;
// 3Dカメラのコントローラー
CameraController_3D cameraController_3D;

Scene* pScene;

// 初期化処理
void App::Init()
{
	Scene_I->LoadScene("Assets/SceneData/test.txt");

	pScene = new Scene();
	camera.Init(ProjectionType::Perspective);
	Render_I->SetCamera(&camera);

	// モデル操作パネルの初期化
	modelControlPanel.Init("Model Control Panel");
	modelControlPanel.AddControlTarget(
		Scene_I->GetCurrentScene()->GetGameObjectById(0)
	);

	modelControlPanel.AddControlTarget(
		Scene_I->GetCurrentScene()->GetGameObjectById(1)
	);


	// モデルのデータを保存するための変数
	camera.Init(ProjectionType::Perspective);
	camera.SetPosition(Vector3f(0.0f, 10.0f, -50.0f));
	// レンダリングマネージャーにカメラを設定する
	Render_I->SetCamera(&camera);
	// カメラを設定する
	cameraController_3D.SetCamera(&camera);
	// カメラの操作モードをフリーカメラモードにする
	cameraController_3D.SetCameraMode(CameraMode::FreeCamera);
}

// 更新処理
void App::Update()
{
	cubeObject.Update();
	// カメラコントローラーを更新する
	cameraController_3D.Update();
}

// 描画処理
void App::Render()
{
	cubeObject.Render();
	Scene_I->GetCurrentScene()->Render();
}

// 後片付け
void App::Term()
{
	Scene_I->SaveCurrentScene();
}