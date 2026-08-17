#pragma once

#include "Framework/Math/Vector.h"
#include "Framework/Math/Quaternion.h"

#include <vector>

class Transform
{
public:
	// コンストラクタ
	Transform();
	// デストラクター
	~Transform();

	// 親トランスフォームを設定する
	void SetParent(Transform* _pTransform);
	// 親トランスフォームを取得する
	Transform* GetParent() const;

	// 子トランスフォームを追加する
	void AddChild(Transform* _pTransform);
	// 子トランスフォームを削除する
	void RemoveChild(Transform* _pTransform);

	// 特定の子供トランスフォームを取得する
	Transform* GetChild(const int _num) const;

	// 全ての子供トランスフォームを取得する
	const std::vector<Transform*>& GetChildren() const;

	// 前方向ベクトルを取得する
	Vector3f GetForward() const;
	// 右方向ベクトルを取得する
	Vector3f GetRight() const;
	// 上方向ベクトルを取得する
	Vector3f GetUp() const;

	// ローカル座標を取得する
	Vector3f GetLocalPosition() const;
	// ローカル回転を取得する
	Quaternion GetLocalRotation() const;
	// ローカルスケールを取得する
	Vector3f GetLocalScale() const;

	// ローカル座標を設定する
	void SetLocalPosition(const Vector3f& _position);
	// ローカル回転を設定する
	void SetLocalRotation(const Quaternion& _rotation);
	// ローカルスケールを設定する
	void SetLocalScale(const Vector3f& _scale);

		
	// ワールド座標を取得する
	Vector3f GetWorldPosition() const;
	// ワールド回転を取得する
	Quaternion GetWorldRotation() const;
	// ワールドスケールを取得する
	Vector3f GetWorldScale() const;

	// ワールド座標を設定する
	void SetWorldPosition(const Vector3f& _position);
	// ワールド回転を設定する
	void SetWorldRotation(const Quaternion& _rotation);
	// ワールドスケールを設定する
	void SetWorldScale(const Vector3f& _scale);

	// ワールド行列を取得する
	DirectX::XMMATRIX GetWorldMatrix() const;
protected:
	// 「更新が必要」と設定する
	void _setDirty();

		
private:
	// ワールド行列を更新する
	void _updateWorldData() const;

	// ローカル行列を取得する
	DirectX::XMMATRIX _getLocalMatrix() const;

private:
	// ローカル位置
	Vector3f m_localPosition;
	// ローカル回転
	Quaternion m_localRotation;
	// ローカルスケール
	Vector3f m_localScale;

	// ワールド位置
	mutable Vector3f m_worldPosition;
	// ワールド回転
	mutable Quaternion m_worldRotation;
	// ワールドスケール
	mutable Vector3f m_worldScale;
private:
	// 親トランスフォーム
	Transform* m_pParent;
	// 子トランスフォーム
	std::vector<Transform*> m_children;

	// ワールド行列
	mutable DirectX::XMMATRIX m_worldMatrix;

	// ワールド行列の更新が必要かを表すプロパティ
	mutable bool m_isDirty;
	
public:
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(
		Transform,
		m_localPosition,
		m_localRotation,
		m_localScale
	)
};
