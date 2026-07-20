#pragma once

#include "Framework/Runtime/Camera.h"

class CameraController
{
public:
	// 初期化処理
	virtual void Init(Runtime::Camera* _pCamera) {}
	
	void SetCamera(Runtime::Camera* _pCamera) {
		m_pCamera = _pCamera;
	}

	// 更新処理
	virtual void Update() {}


protected:
	// コントロールするカメラ
	Runtime::Camera* m_pCamera;
};