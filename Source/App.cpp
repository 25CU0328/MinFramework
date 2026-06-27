
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework/Framework.h"


#include "Framework/Runtime/Camera.h"
#include "Framework/Runtime/Sprite.h"
#include "Framework/Runtime/Model.h"

#include "Framework/Assets/AssetData/MaterialData.h"

Runtime::Model chairModel;
Runtime::Model cubeModel;
Runtime::Camera camera;
Runtime::Sprite sprite;
// 初期化処理
void App::Init()
{
	Render_I->SetCamera(&camera);

	ModelData modelData;
	if (Assets_I->LoadModelFile("Assets/Models/Chair.obj", modelData))
	{
		chairModel.Init(modelData, "Assets/Materials/NormalViewMaterial.txt");
	}

	if (Assets_I->LoadModelFile("Assets/Models/Cube.obj", modelData))
	{
		cubeModel.Init(modelData);
	}

	camera.Init(Runtime::ProjectionType::Perspective);

	camera.SetPosition(Vector3f(0.0f, 50.0f, -100.0f));
}
void UpdateCamera()
{
	const float moveSpeed = 40.0f * (float)Time_I->GetDeltaTime();
	
	// 回転速度を 9O度/毎秒にする
	const float DegToRad = (float)DirectX::XM_PI / 180.0f;
	const float rotateSpeed = 90.0f * DegToRad * (float)Time_I->GetDeltaTime();
	// -----------
	// カメラ移動
	// -----------
	if (GetAsyncKeyState('W') & 0x8000)
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f forwardOffset = camera.GetFront() * moveSpeed;

		camera.SetPosition(cameraPos + forwardOffset);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f forwardOffset = camera.GetFront() * -moveSpeed;

		camera.SetPosition(cameraPos + forwardOffset);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f rightOffset = camera.GetRight() * moveSpeed;

		camera.SetPosition(cameraPos + rightOffset);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f rightOffset = camera.GetRight() * -moveSpeed;

		camera.SetPosition(cameraPos + rightOffset);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		Vector3f cameraPos = camera.GetPosition();
		cameraPos.y += moveSpeed;

		camera.SetPosition(cameraPos);
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		Vector3f cameraPos = camera.GetPosition();
		cameraPos.y -= moveSpeed;

		camera.SetPosition(cameraPos);
	}

	// -----------
	// カメラ回転
	// -----------
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.x -= rotateSpeed;

		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.x += rotateSpeed;

		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.y += rotateSpeed;

		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.y -= rotateSpeed;

		camera.SetRotation(cameraRot);
	}
}

void UpdateImage()
{
	const float moveSpeed = 60.0f * (float)Time_I->GetDeltaTime();
	
	// 回転速度を 45度/毎秒にする
	const float DegToRad = (float)DirectX::XM_PI / 180.0f;
	const float rotateSpeed = 45.0f * DegToRad * (float)Time_I->GetDeltaTime();

	if (GetAsyncKeyState('W') & 0x8000)
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(0.0f, 1.0f) * moveSpeed);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(0.0f, 1.0f) * -moveSpeed);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(1.0f, 0.0f) * -moveSpeed);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(1.0f, 0.0f) * moveSpeed);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		float spriteRot = sprite.GetRotation() - rotateSpeed;
		sprite.SetRotation(spriteRot);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		float spriteRot = sprite.GetRotation() + rotateSpeed;
		sprite.SetRotation(spriteRot);
	}
}
// 更新処理
void App::Update()
{
	UpdateCamera();
	
}

// 描画処理
void App::Render()
{
	//sprite.Draw();
	chairModel.Draw();
	cubeModel.Draw();
}

// 後片付け
void App::Term()
{

}