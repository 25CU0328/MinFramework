#pragma once

#include "Render/Resource/ConstantBuffer.h"

#include "DirectXMath.h"
using namespace DirectX;

// フレームワークユーサが弄る
namespace Runtime
{
	enum class ProjectionType
	{
		Perspective,	// 透視投影
		Orthographic	// 正投影
	};

	class Camera
	{
		// オブジェクトの複製を禁止する
		Camera(const Camera&) = delete;
		// オペレーターによるコピーを禁止する
		Camera operator = (const Camera&) = delete;

	public:
		// コンストラクタ
		Camera();
		// デストラクター
		~Camera();

		// 初期化処理
		void Init();
		// 位置を設定する
		void SetPosition(const DirectX::XMFLOAT3& _position);

		// 回転角度を設定する
		void SetRotation(const DirectX::XMFLOAT3& _rotation);

		void SetView(
			float _fov,
			float _aspect,
			float _nearPlaneDistance,
			float _farPlaneDistance
		);
		// カメラ位置を取得する
		XMFLOAT3 GetPosition() const;
		// カメラの回転角度を取得する
		XMFLOAT3 GetRotation() const;

		DirectX::XMMATRIX GetViewMatrix() const;

		DirectX::XMMATRIX GetProjectionMatrix() const;

		DirectX::XMMATRIX GetViewProjectionMatrix() const;

	private:

		float m_fov;	// 画角
		float m_aspect;	// アスペクト比
		float m_nearZ;	// 近接平面
		float m_farZ;	// 遠方平面

		XMFLOAT3 m_position; // カメラ位置
		XMFLOAT3 m_rotation; // カメラ回転角度

		ProjectionType m_projectionType;
	};
}