
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework/Framework.h"

#include "AppDef.h"

#include "Framework/Runtime/Camera.h"
#include "Framework/Runtime/Sprite.h"
#include "Framework/Runtime/Model.h"

#include "Framework/Assets/AssetData/MaterialData.h"
#include "Panels/ImageControlPanel.h"
#include "Panels/ModelControlPanel.h"
#include "Panels/CameraControlPanel.h"
#include "CameraController/CameraController_3D.h"
Runtime::Model donutModel;
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
	
	ModelData modelData;
	if (Assets_I->LoadModelFile("Assets/Models/Donut.obj", modelData))
	{
		donutModel.Init(modelData, "Assets/Materials/NormalViewMaterial.txt");
		donutModel.SetName("Donut");
		donutModel.SetPosition(Vector3f(0.0f, 10.0f, 0.0f));
	}

	if (Assets_I->LoadModelFile("Assets/Models/Cube.obj", modelData))
	{
		cubeModel.Init(modelData);
		cubeModel.SetName("Cube");
		coneModel.SetTexture(Assets_I->GetTexture("Assets/Images/Wood.png"));
		cubeModel.SetPosition(Vector3f(0.0f, 10.0f, 0.0f));
	}
	
	if (Assets_I->LoadModelFile("Assets/Models/Cone.obj", modelData))
	{
		coneModel.Init(modelData);
		coneModel.SetName("Cone");
		coneModel.SetTexture(Assets_I->GetTexture("Assets/Images/MossyRock.jpg"));
		coneModel.SetPosition(Vector3f(10.0f, 10.0f, 0.0f));
	}

	if (Assets_I->LoadModelFile("Assets/Models/Ground.obj", modelData))
	{
		groundModel.Init(modelData);
		groundModel.SetName("Ground");
		groundModel.SetTexture(Assets_I->GetTexture("Assets/Images/MossyRock.jpg"));
	}

	camera.Init(Runtime::ProjectionType::Perspective);
	camera.SetPosition(Vector3f(0.0f, 10.0f, -50.0f));
	Render_I->SetCamera(&camera);
	cameraController_3D.SetCamera(&camera);
	cameraController_3D.SetCameraMode(CameraMode::FreeCamera);
	cameraController_3D.SetOrbitDistance(300.0f);

	modelControlPanel.Init("Model Control Panel");
	modelControlPanel.AddControlTarget(&cubeModel);
	modelControlPanel.AddControlTarget(&donutModel);
	modelControlPanel.AddControlTarget(&coneModel);

	cameraControlPanel.Init("Camera Control Panel");
	cameraControlPanel.SetCamera(&camera);
	cameraControlPanel.SetCameraController(&cameraController_3D);
	cameraControlPanel.SetPanelPosition(
		Vector2f(static_cast<float>(WINDOW_WIDTH) - cameraControlPanel.GetPanelSize().x, 0.0f)
	);

	cameraControlPanel.AddTargetModel(&cubeModel);
	cameraControlPanel.AddTargetModel(&donutModel);
	cameraControlPanel.AddTargetModel(&coneModel);
}

// 更新処理
void App::Update()
{
	cameraController_3D.Update();
}

// 描画処理
void App::Render()
{
	donutModel.Draw();
	cubeModel.Draw();
	coneModel.Draw();
	groundModel.Draw();
}

// 後片付け
void App::Term()
{

}