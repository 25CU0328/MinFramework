

#include "RectCollider.h"

// コンストラクタ
RectCollider::RectCollider(Vector2f _position, Vector2f _size)
{
    m_position = Vector3f(_position.x, _position.y, 0.0f);
    m_size = _size;
    m_type = ColliderType::Rect;
}

// サイズを設定する
void RectCollider::SetSize(const Vector2f& size)
{
    m_size = size;
}

// サイズを取得する
Vector2f RectCollider::GetSize() const
{
    return m_size;
}

Vector2f RectCollider::GetPosition() const
{
    return Vector2f(m_position.x, m_position.y);
}