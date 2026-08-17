
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework/Framework.h"

#include "AppDef.h"

#include "Framework/Runtime/Camera.h"
#include "Framework/Runtime/Sprite.h"
#include "Framework/Runtime/Model.h"

#include "Framework/Assets/AssetData/MaterialData.h"
#include "Panels/ModelControlPanel.h"
#include "Panels/CameraControlPanel.h"
#include "CameraController/CameraController_3D.h"
Runtime::Model chairModel;
Runtime::Model cubeModel;
Runtime::Model coneModel;
Runtime::Model groundModel;

Runtime::Camera camera;

// モデルの操作パネル
ModelControlPanel modelControlPanel;
// カメラの操作パネル
CameraControlPanel cameraControlPanel;
// 3Dカメラのコントローラー
CameraController_3D cameraController_3D;


// 初期化処理
void App::Init()
{
	camera.Init(Runtime::ProjectionType::Perspective);
	Render_I->SetCamera(&camera);

	// モデル操作パネルの初期化
	modelControlPanel.Init("Model Control Panel");

	// カメラ操作パネルの初期化処理
	cameraControlPanel.Init("Camera Control Panel");

	// モデルのデータを保存するための変数
	ModelData modelData;

	// 椅子のモデルを読み込む
	if (Assets_I->LoadModelFile("Assets/Models/Chair.obj", modelData))
	{
		// モデルの初期化
		chairModel.Init(modelData, "Assets/Materials/NormalViewMaterial.txt");
		// オブジェクト名を設定する
		chairModel.SetName("Chair");
		// 位置を設定する
		chairModel.GetTransform().SetWorldPosition(Vector3f(0.0f, 1.0f, 0.0f));
		// モデル操作パネルに追加する
		modelControlPanel.AddControlTarget(&chairModel);
		// カメラ操作パネルに追加する
		cameraControlPanel.AddTargetModel(&chairModel);
	}

	// 立方体を読み込む
	if (Assets_I->LoadModelFile("Assets/Models/Cube.obj", modelData))
	{
		// モデルの初期化
		cubeModel.Init(modelData);
		// オブジェクト名を設定する
		cubeModel.SetName("Cube");
		// 位置を設定する
		cubeModel.GetTransform().SetWorldPosition(Vector3f(0.0f, 10.0f, 0.0f));
		// モデル操作パネルに追加する
		modelControlPanel.AddControlTarget(&cubeModel);
		// カメラ操作パネルに追加する
		cameraControlPanel.AddTargetModel(&cubeModel);
	}

	// 円錐のモデルを読み込む
	if (Assets_I->LoadModelFile("Assets/Models/Cone.obj", modelData))
	{
		// モデルの初期化
		coneModel.Init(modelData);
		// オブジェクト名を設定する
		coneModel.SetName("Cone");
		// テクスチャを設定する
		coneModel.SetTexture(Assets_I->GetTexture("Assets/Images/Wood.png"));
		// 位置を設定する
		coneModel.GetTransform().SetWorldPosition(Vector3f(10.0f, 10.0f, 0.0f));
		// モデル操作パネルに追加する
		modelControlPanel.AddControlTarget(&coneModel);
		// カメラ操作パネルに追加する
		cameraControlPanel.AddTargetModel(&coneModel);
	}

	// 地面のモデルを読み込む
	if (Assets_I->LoadModelFile("Assets/Models/Ground.obj", modelData))
	{
		// モデルの初期化
		groundModel.Init(modelData);
		// オブジェクト名を設定する
		groundModel.SetName("Ground");
		// テクスチャを設定する
		groundModel.SetTexture(Assets_I->GetTexture("Assets/Images/MossyRock.jpg"));
	}

	camera.Init(Runtime::ProjectionType::Perspective);
	camera.SetPosition(Vector3f(0.0f, 10.0f, -50.0f));

	// レンダリングマネージャーにカメラを設定する
	Render_I->SetCamera(&camera);
	// カメラを設定する
	cameraController_3D.SetCamera(&camera);
	// カメラの操作モードをフリーカメラモードにする
	cameraController_3D.SetCameraMode(CameraMode::FreeCamera);

	// カメラを設定する
	cameraControlPanel.SetCamera(&camera);
	// カメラコントローラーを設定する
	cameraControlPanel.SetCameraController(&cameraController_3D);
	// ウィンドウの右上に設定するお
	cameraControlPanel.SetPanelPosition(
		Vector2f(static_cast<float>(WINDOW_WIDTH) - cameraControlPanel.GetPanelSize().x, 0.0f)
	);

	
}

// 更新処理
void App::Update()
{
	// カメラコントローラーを更新する
	cameraController_3D.Update();
}

// 描画処理
void App::Render()
{
	// 椅子を描画する
	chairModel.Draw();
	// 立方体を描画する
	cubeModel.Draw();
	// 円錐を描画する
	coneModel.Draw();
	// 地面を描画する
	groundModel.Draw();
}

// 後片付け
void App::Term()
{

}