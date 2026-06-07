#pragma once

#include <DirectXMath.h>

#include "Assets/Image/ImageData.h"
#include "RenderObject.h"

#include "Math/Vector2.h"

namespace Runtime
{
	class Sprite : RenderObject
	{
		// コピーを禁止する
		Sprite(const Sprite&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const Sprite&) = delete;

	public:
		// コンストラクタ
		Sprite();
		// デストラクター
		~Sprite();

		// 初期化処理
		void Init(
			const std::string _filePath, 
			const Vector2f _size, 
			const Vector2f _position
		);

		// 初期化処理
		void Init(
			const std::string _filePath,
			const float _sizeX,
			const float _sizeY,
			const float _positionX,
			const float _positionY
		);


		// スプライトを描画する
		void Draw();

		// 位置を設定する
		void SetPosition(const Vector2f& _position);
		// 位置を設定する
		void SetPosition(const float _x, const float _y);
		// 回転角度を設定する
		void SetRotation(const int _degree);
		// サイズを設定する
		void SetSize(const Vector2f& _size);
		// サイズを設定する
		void SetSize(const float _x, const float _y);

		// 位置を取得する
		Vector2f GetPosition() const;
		// サイズを取得する
		Vector2f GetSize() const;
		// 回転角度(逆時計回り)を取得する
		int GetRotation() const;

		// レンダリング用のデータを取得する
		RenderData GetData();
		// ワールド行列を取得する
		DirectX::XMMATRIX GetWorldMatrix();
	private:
		// バッファーの初期化 (RenderObjectから継承した)
		void _initBuffers();

		// 位置
		Vector2f m_position;
		// サイズ
		Vector2f m_size;
		// 回転角度(逆時計回り) (Degree)
		int m_rotation;
	};
}