#pragma once

#include "Mesh.h"
#include "Framework/Assets/Model/ModelData.h"

namespace Runtime
{
	class Model
	{
	public:

		// 初期化処理
		bool Init(
			ModelData _data, 
			std::string _materialName = ""
		);

		// メッシュを描画する
		void Draw();

		// 位置を設定
		void SetPosition(const Vector3f& _position);
		// 位置を取得する
		Vector3f GetPosition() const;

		// 回転を設定する
		void SetRotation(const Vector3f& _rotation);
		// 回転を所得する
		Vector3f GetRotation() const;
		// 座標変換用の行列を取得する
		XMMATRIX GetTransformMatrix() const;

		// スケイルを設定
		void SetScale(const Vector3f& _scale);
		// スケイルを取得する
		Vector3f GetScale() const;


		// 描画の優先順位を設定する
		void SetRenderPriority(const int _priority);
		// 描画の優先順位を取得する
		int GetRenderPriority() const;

		// モデル名を設定する
		void SetName(const std::string _name);
		// モデル名を取得する
		std::string GetName() const;
	private:
		// モデルにある全てのメッシュ
		std::vector<Mesh*> m_pMeshes;

		
		Vector3f m_position;	// 位置
		Vector3f m_rotation;	// 回転
		Vector3f m_scale;		// スケイル
		

		int m_renderPriority;	// 描画の優先順位

		std::string m_name;	// 名前
	};
}