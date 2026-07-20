
#include "CameraController.h"
#include "Framework/Runtime/Model.h"

// カメラの操作モードを表す列挙型
enum class CameraMode {
	FreeCamera,
	Orbit,
};

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
private:
	// フリーカメラの更新処理
	void _updateFreeCamera();
	// カメラの更新処理
	void _updateOrbitCamera();

private:
	CameraMode m_cameraMode;	// カメラの操作モード
	float m_cameraRotateSpeed;	// カメラの回転速度

	// FreeCameraモードで使われるプロパティ
	float m_cameraMoveSpeed;	// カメラの移動速度

	// Orbitモードで使われるプロパティ
	float m_orbitDistance;			// 回る時の距離
	Runtime::Model m_orbitTarget;	// 回る時のターゲット
};