
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
Runtime::Model chairModel;
Runtime::Model cubeModel;
Runtime::Camera camera;
Runtime::Sprite sprite;
Runtime::Sprite sprite2;

ImageControlPanel kirbyControlPanel;
ImageControlPanel pikaChuControlPanel;
ModelControlPanel modelControlPanel;
CameraControlPanel cameraControlPanel;

CameraController_3D cameraController_3D;
// 初期化処理
void App::Init()
{
	camera.Init(Runtime::ProjectionType::Perspective);
	Render_I->SetCamera(&camera);
	
	ModelData modelData;
	if (Assets_I->LoadModelFile("Assets/Models/Chair.obj", modelData))
	{
		chairModel.Init(modelData, "Assets/Materials/NormalViewMaterial.txt");
		chairModel.SetName("Chair");
	}

	if (Assets_I->LoadModelFile("Assets/Models/Cube.obj", modelData))
	{
		cubeModel.Init(modelData);
		cubeModel.SetName("Cube");
		cubeModel.SetPosition(Vector3f(0.0f, 50.0f, 0.0f));
	}
	
	camera.Init(Runtime::ProjectionType::Perspective);
	camera.SetPosition(Vector3f(0.0f, 50.0f, -100.0f));
	Render_I->SetCamera(&camera);
	cameraController_3D.SetCamera(&camera);
	cameraController_3D.SetCameraMode(CameraMode::FreeCamera);
	cameraController_3D.SetOrbitDistance(300.0f);

	modelControlPanel.Init("Model Control Panel");
	modelControlPanel.AddControlTarget(&cubeModel);
	modelControlPanel.AddControlTarget(&chairModel);
	
	cameraControlPanel.Init("Camera Control Panel");
	cameraControlPanel.SetCamera(&camera);
	cameraControlPanel.SetPanelPosition(
		Vector2f(static_cast<float>(WINDOW_WIDTH) - cameraControlPanel.GetPanelSize().x, 0.0f)
	);
	/*
	sprite.Init(
		Vector2f(100.0f, 100.0f),
		Vector2f(-50.0f, 0.0f),
		"Assets/Images/Kirby.jpg"
	);
	sprite.SetRenderPriority(2);

	sprite.SetTextureRange(0.0f, 0.0f, 0.5f, 0.5f);
	sprite2.Init(
		Vector2f(100.0f, 100.0f),
		Vector2f(50.0f, 0.0f),
		"Assets/Images/Pikachu.jpg"
	);
	sprite2.SetRenderPriority(5);
	kirbyControlPanel.Init("Pink_Manju Control Panel", &sprite);
	pikaChuControlPanel.Init("Electric_Mouse Control Panel", &sprite2);
	pikaChuControlPanel.SetPanelPosition(
		Vector2f(static_cast<float>(WINDOW_WIDTH) - pikaChuControlPanel.GetPanelSize().x, 0.0f)
	);*/
}

void UpdateCamera2D()
{
	if (!Input_I->IsMousePressed(MouseButton::Right))
	{
		Input_I->SetCursorVisible(true);
		return;
	}

	Input_I->SetCursorVisible(false);


	const float moveSpeed = 60.0f * (float)Time_I->GetDeltaTime();
	
	// 回転速度を 45度/毎秒にする
	const float DegToRad = (float)DirectX::XM_PI / 180.0f;
	const float rotateSpeed = 45.0f * DegToRad * (float)Time_I->GetDeltaTime();

	// -----------
	// カメラ回転
	// -----------
	{
		Vector2f mouseDelta = Input_I->GetMousePositionDelta();
		mouseDelta *= moveSpeed;
		Vector3f cameraPos = camera.GetPosition();

		cameraPos.x -= mouseDelta.x;
		cameraPos.y += mouseDelta.y;

		camera.SetPosition(cameraPos);
	}
}

// 更新処理
void App::Update()
{
	cameraController_3D.Update();
	// UpdateCamera2D();
}

// 描画処理
void App::Render()
{
	// sprite.Draw();
	// sprite2.Draw();
	chairModel.Draw();
	cubeModel.Draw();
}

// 後片付け
void App::Term()
{

}