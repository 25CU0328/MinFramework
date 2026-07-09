

#include "BoxCollider.h"

// コンストラクタ
BoxCollider::BoxCollider(Vector2f _position, Vector2f _size)
{
    m_position = _position;
    m_size = _size;
    m_type = ColliderType::Box;
}

// 位置を設定する
void BoxCollider::SetPosition(const Vector2f& pos)
{
    m_position = pos;
}

// サイズを設定する
void BoxCollider::SetSize(const Vector2f& size)
{
    m_size = size;
}

// 位置を取得する
Vector2f BoxCollider::GetPosition() const
{
    return m_position;
}

// サイズを取得する
Vector2f BoxCollider::GetSize() const
{
    return m_size;
}