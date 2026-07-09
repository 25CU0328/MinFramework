#pragma once

#include "Collider.h"
#include "Framework/Math/Vector2.h"

class BoxCollider : public Collider
{
public:
    // コンストラクタ
    BoxCollider(
        Vector2f _position = Vector2f(0.0f, 0.0f),
        Vector2f _size = Vector2f(0.0f, 0.0f)
    );

    // 位置を設定する
    void SetPosition(const Vector2f& pos);

    // サイズを設定する
    void SetSize(const Vector2f& size);

    // 位置を取得する
    Vector2f GetPosition() const;

    // サイズを取得する
    Vector2f GetSize() const;

private:
    Vector2f m_size;
    Vector2f m_position;
};