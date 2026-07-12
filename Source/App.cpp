
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework/Framework.h"


#include "Framework/Runtime/Camera.h"
#include "Framework/Runtime/Sprite.h"
#include "Framework/Runtime/Model.h"

#include "Framework/Assets/AssetData/MaterialData.h"
#include "imgui.h"
Runtime::Model chairModel;
Runtime::Model cubeModel;
Runtime::Camera camera;
Runtime::Sprite sprite;
Runtime::Sprite sprite2;
RectCollider boxCollider1;
RectCollider boxCollider2;
void OnCollision(CollisionEvent _event);
// 初期化処理
void App::Init()
{
	Render_I->SetCamera(&camera);
	
	sprite.Init(
		Vector2f(50.0f, 50.0f),
		Vector2f(0.0f, 0.0f),
		"Assets/Images/Mika.jpg"
	);
	sprite.SetRenderPriority(2);

	boxCollider1.SetSize(Vector2f(50.0f, 50.0f));
	boxCollider1.SetPosition(Vector2f(0.0f, 0.0f));
	boxCollider1.SetCallback(OnCollision);
	boxCollider1.SetLayer(1);
	boxCollider1.AddHitLayer(2);
	Collision_I->Register(&boxCollider1);

	sprite.SetTextureRange(0.0f, 0.0f, 0.5f, 0.5f);

	sprite2.Init(
		Vector2f(50.0f, 50.0f),
		Vector2f(0.0f, 0.0f)
	);
	sprite2.SetRenderPriority(5);

	boxCollider2.SetSize(Vector2f(50.0f, 50.0f));
	boxCollider2.SetPosition(Vector2f(0.0f, 0.0f));
	boxCollider2.SetLayer(2);
	Collision_I->Register(&boxCollider2);
	/*ModelData modelData;
	if (Assets_I->LoadModelFile("Assets/Models/Chair.obj", modelData))
	{
		chairModel.Init(modelData, "Assets/Materials/NormalViewMaterial.txt");
	}

	if (Assets_I->LoadModelFile("Assets/Models/Cube.obj", modelData))
	{
		cubeModel.Init(modelData);
	}*/

	camera.Init(Runtime::ProjectionType::Orthographic);

	//camera.SetPosition(Vector3f(0.0f, 50.0f, -100.0f));
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
	if (Input_I->GetKeyPressed('W'))
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f forwardOffset = camera.GetFront() * moveSpeed;

		camera.SetPosition(cameraPos + forwardOffset);
	}
	if (Input_I->GetKeyPressed('S'))
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f forwardOffset = camera.GetFront() * -moveSpeed;

		camera.SetPosition(cameraPos + forwardOffset);
	}
	if (Input_I->GetKeyPressed('A'))
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f rightOffset = camera.GetRight() * moveSpeed;

		camera.SetPosition(cameraPos + rightOffset);
	}
	if (Input_I->GetKeyPressed('D'))
	{
		Vector3f cameraPos = camera.GetPosition();
		Vector3f rightOffset = camera.GetRight() * -moveSpeed;

		camera.SetPosition(cameraPos + rightOffset);
	}
	if (Input_I->GetKeyPressed('Q'))
	{
		Vector3f cameraPos = camera.GetPosition();
		cameraPos.y += moveSpeed;

		camera.SetPosition(cameraPos);
	}
	if (Input_I->GetKeyPressed('E'))
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

	if (Input_I->GetKeyPressed('W'))
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(0.0f, 1.0f) * moveSpeed);
		boxCollider1.SetPosition(spritePos + Vector2f(0.0f, 1.0f) * moveSpeed);
	}
	if (Input_I->GetKeyPressed('S'))
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(0.0f, 1.0f) * -moveSpeed);
		boxCollider1.SetPosition(spritePos + Vector2f(0.0f, 1.0f) * -moveSpeed);
	}
	if (Input_I->GetKeyPressed('A'))
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(1.0f, 0.0f) * -moveSpeed);
		boxCollider1.SetPosition(spritePos + Vector2f(1.0f, 0.0f) * -moveSpeed);
	}
	if (Input_I->GetKeyPressed('D'))
	{
		Vector2f spritePos = sprite.GetPosition();

		sprite.SetPosition(spritePos + Vector2f(1.0f, 0.0f) * moveSpeed);
		boxCollider1.SetPosition(spritePos + Vector2f(1.0f, 0.0f) * moveSpeed);
	}
	if (Input_I->GetKeyPressed(VK_RIGHT))
	{
		float spriteRot = sprite.GetRotation() - rotateSpeed;
		sprite.SetRotation(spriteRot);
	}
	if (Input_I->GetKeyPressed(VK_LEFT))
	{
		float spriteRot = sprite.GetRotation() + rotateSpeed;
		sprite.SetRotation(spriteRot);
	}
}

void OnCollision(CollisionEvent _event)
{
	/*
	if (_event.type == CollisionEventType::Enter)
	{
		printf("Enterrrr\n");
	}
	if (_event.type == CollisionEventType::Stay)
	{
		printf("Stayyyyy\n");
	}
	if (_event.type == CollisionEventType::Exit)
	{
		printf("Exitttt\n");
	}*/
}
// 更新処理
void App::Update()
{
	// UpdateCamera();
	UpdateImage();
}

// 描画処理
void App::Render()
{
	sprite.Draw();
	sprite2.Draw();
	//chairModel.Draw();
	//cubeModel.Draw();
}

// 後片付け
void App::Term()
{

}