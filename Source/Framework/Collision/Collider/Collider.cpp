
#include "Collider.h"

// 衝突が発生する時呼ばれるメソッド
void Collider::OnCollision(CollisionEvent _collisionEvent)
{
	if (m_collisionCallback)
	{
		m_collisionCallback(_collisionEvent);
	}
}

// コライダーの種類を取得する
ColliderType Collider::GetColliderType() const
{
	return m_type;
}

// コールバック関数を設定する
void Collider::SetCallback(std::function<void(CollisionEvent)> _callback)
{
	m_collisionCallback = _callback;
}


// 位置を設定する
void Collider::SetPosition(const float _x, const float _y)
{
	m_position = Vector3(_x, _y, 0.0f);
}

void Collider::SetPosition(const Vector2f _newPosition)
{
	m_position = Vector3(_newPosition.x, _newPosition.y, 0.0f);
}
void Collider::SetPosition(const float _x, const float _y, const float _z)
{
	m_position = Vector3(_x, _y, _z);
}
void Collider::SetPosition(const Vector3f _newPosition)
{
	m_position = _newPosition;
}

// 位置を取得する
Vector3f Collider::GetPosition() const
{
	return m_position;
}


#pragma region Layer
// 衝突レイヤーを追加する
void Collider::AddHitLayer(int _layer)
{
	m_hitLayer |= (1 << _layer);
}
// 衝突レイヤーを削除する
void Collider::RemoveHitLayer(int _layer)
{
	m_hitLayer &= _layer;
}
// 衝突レイヤーをリセット
void Collider::ClearHitLayer()
{
	m_hitLayer = 0;
}
// 衝突対象レイヤーを取得する
int Collider::GetHitLayer() const
{
	return m_hitLayer;
}

// コライダー自身のレイヤーを設定する
void Collider::SetLayer(int _layer)
{
	m_layer = (1 << _layer);
}
// コライダーのレイヤーを取得する
int Collider::GetLayer() const
{
	return m_layer;
}
#pragma endregion