#pragma once

#include "Framework/Math/Vector.h"
#include "Framework/Math/Quaternion.h"
#include "Framework/Runtime/Transform.h"

#include <string>
#include <vector>
namespace Runtime
{
	class GameObject
	{
	public:
		// 初期化処理
		virtual void Init() {}
		// 更新処理
		virtual void Update() {}
		// 描画処理
		virtual void Render() {}
		// 後片付け処理
		virtual void Term() {}
	public:
		// 位置を設定する
		void SetPosition(const Vector2f& _position);
		// 位置を設定
		void SetPosition(const Vector3f& _position);
		// 位置を取得する
		Vector3f GetPosition() const;

		// 回転を設定する
		void SetRotation(const Quaternion& _rotation);
		// 回転を設定する
		void SetRotationEuler(const Vector3f& _rotation);
		// 回転を取得する
		Quaternion GetRotation() const;
		// 回転を取得する
		Vector3f GetRotationEuler() const;

		// スケールを設定する
		void SetScale(const Vector3f& _scale);
		// スケールを取得する
		Vector3f GetScale() const;

		// オブジェクト名を設定する
		void SetName(std::string _name);
		// オブジェクト名を取得する
		std::string GetName() const;

		void SetParent(GameObject* _pObject);
		GameObject* GetParent() const;
	protected:
		std::string m_objectName;		// オブジェクト名

		Vector3f m_position;	// 位置
		Quaternion m_rotation;	// 回転
		Vector3f m_scale;		// スケール

		Transform m_transform;

		GameObject* m_pParentObject;	// 親オブジェクト
		
	};
}