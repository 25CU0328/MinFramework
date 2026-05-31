
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework.h"


#include "RuntimeResource/Camera.h"
#include "RuntimeResource/Model.h"
Runtime::Model testModel1;
Runtime::Model testModel2;

Runtime::Camera camera;

// 初期化処理
void App::Init()
{
	ModelData modelData = {};
	if (!Assets_I->LoadModelFile("Assets/Models/Chair.obj", modelData))
	{
		printf("Failed to Load Chair.obj\n");
		return;
	}
	testModel1.Init(modelData);

	if (!Assets_I->LoadModelFile("Assets/Models/Cube.obj", modelData))
	{
		printf("Failed to Load Cube.obj\n");
		return;
	}
	testModel2.Init(modelData);

	camera.SetPosition(XMFLOAT3(0, 50, -100));
}

// 更新処理
void App::Update()
{
	const float moveSpeed = 5.0f / 60.0f;
	const float rotateSpeed = 0.001f / 60.0f;
	// -----------
	// カメラ移動
	// -----------
	if (GetAsyncKeyState('W') & 0x8000)
	{
		XMFLOAT3 cameraPos = camera.GetPosition();
		cameraPos.z += moveSpeed;
		camera.SetPosition(cameraPos);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		XMFLOAT3 cameraPos = camera.GetPosition();
		cameraPos.z -= moveSpeed;
		camera.SetPosition(cameraPos);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		XMFLOAT3 cameraPos = camera.GetPosition();
		cameraPos.x -= moveSpeed;
		camera.SetPosition(cameraPos);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		XMFLOAT3 cameraPos = camera.GetPosition();
		cameraPos.x += moveSpeed;
		camera.SetPosition(cameraPos);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		XMFLOAT3 cameraPos = camera.GetPosition();
		cameraPos.y += moveSpeed;
		camera.SetPosition(cameraPos);
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		XMFLOAT3 cameraPos = camera.GetPosition();
		
		cameraPos.y -= moveSpeed;
		camera.SetPosition(cameraPos);
	}

	// -----------
	// カメラ回転
	// -----------
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		XMFLOAT3 cameraRot = camera.GetRotation();
		cameraRot.x -= moveSpeed;
		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		XMFLOAT3 cameraRot = camera.GetRotation();
		cameraRot.x += moveSpeed;
		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		XMFLOAT3 cameraRot = camera.GetRotation();
		cameraRot.y += moveSpeed;
		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		XMFLOAT3 cameraRot = camera.GetRotation();
		cameraRot.y -= moveSpeed;
		camera.SetRotation(cameraRot);
	}
}

// 描画処理
void App::Render()
{
	testModel1.Draw(&camera);
	testModel2.Draw(&camera);
}

// 後片付け
void App::Term()
{

}