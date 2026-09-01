
#include "CameraController.h"
#include "Framework/Runtime/GameObject.h"

// カメラの操作モードを表す列挙型
enum class CameraMode {
	FreeCamera,
	Orbit,
};

class Model; 

class CameraController_3D : public CameraController
{
public:
	// コンストラクタ
	CameraController_3D();
	// デストラクター
	~CameraController_3D();

	// 更新処理
	void Update();

	// カメラの操作方法を設定する
	void SetCameraMode(CameraMode _cameraMode);

	// カメラオービット時の対象を設定する
	void SetOrbitTarget(GameObject* _pOrbitTarget);
	// カメラオービット時の距離を設定する
	void SetOrbitDistance(const float _distance);
	// カメラオービット時の距離を取得する
	float GetOrbitDistance() const;

	// カメラの移動速度を設定する
	void SetCameraMoveSpeed(const float _moveSpeed);
	// カメラの移動速度を取得する
	float GetCameraMoveSpeed() const;

	// 回転速度を取得する
	void SetCameraRotateSpeed(const float _rotateSpeed);
	// 
	float GetCameraRotateSpeed() const;

	// 目標位置を注視するように回転する
	void SetLookAt(const Vector3f _targetPosition);
private:
	// フリーカメラの更新処理
	void _updateFreeCamera(bool _isUpdateOnSetup = false);
	// カメラの更新処理
	void _updateOrbitCamera(bool _isUpdateOnSetup = false);

private:
	CameraMode m_cameraMode;	// カメラの操作モード
	float m_cameraRotateSpeed;	// カメラの回転速度

	// 回転
	float m_yaw;
	float m_pitch;

	// FreeCameraモードで使われるプロパティ
	float m_cameraMoveSpeed;	// カメラの移動速度

	// Orbitモードで使われるプロパティ
	float m_orbitDistance;			// 回る時の距離
	GameObject* m_pOrbitTarget;	// 回る時のターゲット
};