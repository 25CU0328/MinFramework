#pragma once

#include <DirectXMath.h>

#include "Framework/Assets/Image/ImageData.h"
#include "Framework/Assets/Model/ModelData.h"
#include "RenderObject.h"


#include "Framework/Math/Vector2.h"

namespace Runtime
{
	class Sprite : public RenderObject
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
			const Vector2f _size = Vector2f(0.0f, 0.0f),
			const Vector2f _position = Vector2f(0.0f, 0.0f),
			const std::string _texturePath = "",
			const std::string _materialPath = "Assets/Materials/SpriteDefaultMaterial.txt"
		);

		// 初期化処理
		void Init(
			const float _sizeX = 0,
			const float _sizeY = 0,
			const float _positionX = 0,
			const float _positionY = 0,
			const std::string _texturePath = "",
			const std::string _materialPath = "Assets/Materials/DefaultSpriteMaterial.txt"
		);


		// スプライトを描画する
		void Draw();

		// テクスチャを設定する
		void SetTexture(Render::Texture* const _pNewTexture);

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

		/// <summary>
		/// テクスチャの表示範囲を指定する
		/// </summary>
		/// <param name="_x"> 左上位置のx座標 </param>
		/// <param name="_y"> 左上位置のy座標 </param>
		/// <param name="_width"> 幅 </param>
		/// <param name="_height"> 高さ </param>
		void SetTextureRange(
			const float _x,
			const float _y,
			const float _width,
			const float _height
		);

		// レンダリング用のデータを取得する
		RenderData GetData();
		// ワールド行列を取得する
		DirectX::XMMATRIX GetWorldMatrix();


	private:
		// バッファーの初期化 (RenderObjectから継承した)
		void _initBuffers();

	private:
		// 位置
		Vector2f m_position;
		// サイズ
		Vector2f m_size;
		// 回転角度(逆時計回り) (Degree)
		int m_rotation;

		// スプライトを描画する時のメッシュデータ
		MeshData m_meshData;
	};
}