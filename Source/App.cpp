
#include "App.h"

// マネージャーを取得するためインクルード
#include "Framework/Framework.h"


#include "Framework/Runtime/Camera.h"
#include "Framework/Runtime/Sprite.h"

Runtime::Camera camera;
Runtime::Sprite sprite;
// 初期化処理
void App::Init()
{
	Render_I->SetCamera(&camera);

	
	sprite.Init(
		"Assets/Image/Mika.jpg", 
		Vector2f(100, 100), 
		Vector2f(0, 0)
	);

	camera.Init(Runtime::ProjectionType::Orthographic);
}
void UpdateCamera()
{
	const float moveSpeed = 5.0f / 60.0f;
	const float rotateSpeed = 0.1f / 60.0f;
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
		cameraRot.x -= moveSpeed;

		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.x += moveSpeed;

		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.y += moveSpeed;

		camera.SetRotation(cameraRot);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Vector3f cameraRot = camera.GetRotation();
		cameraRot.y -= moveSpeed;

		camera.SetRotation(cameraRot);
	}
}
// 更新処理
void App::Update()
{
	// UpdateCamera();
	const float moveSpeed = 5.0f / 60.0f;
	const int rotateSpeed = 1.0f;

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

// 描画処理
void App::Render()
{
	sprite.Draw();
}

// 後片付け
void App::Term()
{

}