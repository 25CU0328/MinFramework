
#include "CameraController_3D.h"

#include "Framework/Framework.h"
#include "Framework/Math/Math.h"

#include "Framework/Runtime/Model.h"

// コンストラクタ
CameraController_3D::CameraController_3D()
{
	// モード設定
	m_cameraMode = CameraMode::FreeCamera;

	// 回転速度
	m_cameraRotateSpeed = 22.5f;

	// 移動速度
	m_cameraMoveSpeed = 60.0f;

	// オービット距離
	m_orbitDistance = 100.0f;
}
// デストラクター
CameraController_3D::~CameraController_3D()
{

}

// 更新処理
void CameraController_3D::Update()
{
	// モードに対応する更新処理を呼び出す
	switch (m_cameraMode)
	{
	case CameraMode::FreeCamera:
		_updateFreeCamera();
		break;

	case CameraMode::Orbit:
		_updateOrbitCamera();
		break;
	}
}

// カメラの操作方法を設定する
void CameraController_3D::SetCameraMode(CameraMode _cameraMode)
{
	m_cameraMode = _cameraMode;

	switch (m_cameraMode)
	{
	case CameraMode::FreeCamera:
		_updateFreeCamera(true);
		break;

	case CameraMode::Orbit:
		_updateOrbitCamera(true);
		break;
	}
}


// カメラオービット時の対象を設定する
void CameraController_3D::SetOrbitTarget(Runtime::Model* _pOrbitTarget)
{
	m_pOrbitTarget = _pOrbitTarget;

	_updateOrbitCamera(true);
}
// カメラオービット時の距離を設定する
void CameraController_3D::SetOrbitDistance(const float _distance)
{
	m_orbitDistance = _distance;

	_updateOrbitCamera(true);
}
// カメラオービット時の距離を取得する
float CameraController_3D::GetOrbitDistance() const
{
	return m_orbitDistance;
}

// カメラの移動速度を設定する
void CameraController_3D::SetCameraMoveSpeed(const float _moveSpeed)
{
	m_cameraMoveSpeed = _moveSpeed;
}
// カメラの移動速度を取得する
float CameraController_3D::GetCameraMoveSpeed() const
{
	return m_cameraMoveSpeed;
}

// カメラの回転速度を設定する 
void CameraController_3D::SetCameraRotateSpeed(const float _rotateSpeed)
{
	m_cameraRotateSpeed = _rotateSpeed;
}
// カメラの回転速度を取得する 
float CameraController_3D::GetCameraRotateSpeed() const
{
	return m_cameraRotateSpeed;
}


// フリーカメラの更新処理
void CameraController_3D::_updateFreeCamera(bool isUpdateOnSetup)
{
	if (!isUpdateOnSetup) {
		if (!Input_I->IsMousePressed(MouseButton::Right))
		{
			Input_I->SetCursorVisible(true);
			return;
		}

		Input_I->SetCursorVisible(false);
	}
	// 回転速度
	float rotateSpeed = DegToRad(m_cameraRotateSpeed) * (float)Time_I->GetDeltaTime();
	// 移動速度
	float moveSpeed = m_cameraMoveSpeed * (float)Time_I->GetDeltaTime();

	// -----------
	// カメラ移動
	// -----------
	Vector3f cameraPos = m_pCamera->GetPosition();
	Vector3f forwardOffset = Vector3f(0.0f, 0.0f, 0.0f);
	Vector3f rightOffset = Vector3f(0.0f, 0.0f, 0.0f);

	if (Input_I->IsKeyPressed(KeyCode::W))
	{
		forwardOffset += m_pCamera->GetForward() * moveSpeed;
	}
	if (Input_I->IsKeyPressed(KeyCode::S))
	{
		forwardOffset += m_pCamera->GetForward() * -moveSpeed;
	}
	if (Input_I->IsKeyPressed(KeyCode::A))
	{
		rightOffset += m_pCamera->GetRight() * -moveSpeed;
	}
	if (Input_I->IsKeyPressed(KeyCode::D))
	{
		rightOffset += m_pCamera->GetRight() * moveSpeed;
	}
	if (Input_I->IsKeyPressed(KeyCode::Q))
	{
		cameraPos.y += moveSpeed;
	}
	if (Input_I->IsKeyPressed(KeyCode::E))
	{
		cameraPos.y -= moveSpeed;
	}

	m_pCamera->SetPosition(cameraPos + forwardOffset + rightOffset);
	// -----------
	// カメラ回転
	// -----------
	{
		Vector2f mouseDelta = Input_I->GetMousePositionDelta();
		mouseDelta *= rotateSpeed;
		Vector3f cameraRot = m_pCamera->GetRotation();

		cameraRot.x += mouseDelta.y;
		cameraRot.y += mouseDelta.x;

		m_pCamera->SetRotation(cameraRot);
	}
}
// カメラの更新処理
void CameraController_3D::_updateOrbitCamera(bool isUpdateOnSetup)
{
	// オービット時のターゲットが設定されていない場合、処理しない
	if (!m_pOrbitTarget)
		return;

	if (!isUpdateOnSetup) {
		if (!Input_I->IsMousePressed(MouseButton::Right))
		{
			Input_I->SetCursorVisible(true);
			return;
		}

		Input_I->SetCursorVisible(false);
	}
	// 回転速度
	float rotateSpeed = DegToRad(m_cameraRotateSpeed) * (float)Time_I->GetDeltaTime();

	// オービット時のターゲットの位置
	Vector3f modelPos = m_pOrbitTarget->GetPosition();

	// カメラ回転・位置
	Vector3f cameraRot = m_pCamera->GetRotation();
	Vector3f cameraPos = m_pCamera->GetPosition();

	// -----------
	// カメラ回転処理
	// -----------
	if (!isUpdateOnSetup) {
		Vector2f mouseDelta = Input_I->GetMousePositionDelta();
		mouseDelta *= rotateSpeed;

		cameraRot.x += mouseDelta.y;
		cameraRot.y += mouseDelta.x;
		
		m_pCamera->SetRotation(cameraRot);
	}

	// カメラの正面ベクトルを取得し、それの
	cameraPos = modelPos + m_pCamera->GetForward() * (-1.0f) * m_orbitDistance;
	m_pCamera->SetPosition(cameraPos);
}