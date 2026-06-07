#pragma once

#include "DirectXMath.h"
using namespace DirectX;

#include "Framework/Math/Vector.h"

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
		void Init(ProjectionType _type);
		// 位置を設定する
		void SetPosition(const Vector3f& _position);

		// 回転角度を設定する
		void SetRotation(const Vector3f& _rotation);

		// カメラ位置を取得する
		Vector3f GetPosition() const;
		// カメラの回転角度を取得する
		Vector3f GetRotation() const;
		// カメラの前方向ベクトルを取得する
		Vector3f GetFront() const;
		// カメラの右方向ベクトルを取得する
		Vector3f GetRight() const;

		/// <summary>
		/// カメラの投影方式を透視投影に設定する
		/// </summary>
		/// <param name="_fov">		画角				</param>
		/// <param name="_aspect">	アスベスト比		</param>
		/// <param name="_nearZ">	近接平面との距離	</param>
		/// <param name="_farZ">	遠方平面との距離	</param>
		void SetPerspective(
			const float _fov,
			const float _aspect,
			const float _nearZ,
			const float _farZ
		);

		void SetOthographics(
			const float _width,
			const float _height,
			const float _nearZ,
			const float _farZ
		);

		// ○○変換の行列を取得する
		DirectX::XMMATRIX GetViewMatrix() const;
		// ○○変換の行列を取得する
		DirectX::XMMATRIX GetProjectionMatrix() const;
		// ○○変換の行列を取得する
		DirectX::XMMATRIX GetViewProjectionMatrix() const;

	private:

		float m_fov;	// 画角
		float m_aspect;	// アスペクト比

		float m_nearZ;	// 近接平面
		float m_farZ;	// 遠方平面

		float m_viewWidth;	// 正投影範囲の幅広い
		float m_viewHeight; // 正投影範囲の高さ

		Vector3f m_position; // カメラ位置
		Vector3f m_rotation; // カメラ回転角度

		ProjectionType m_projectionType;
	};
}