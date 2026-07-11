#pragma once

#include "Collider.h"
#include "Framework/Math/Vector2.h"

class RectCollider : public Collider
{
public:
    // コンストラクタ
    RectCollider(
        Vector2f _position = Vector2f(0.0f, 0.0f),
        Vector2f _size = Vector2f(0.0f, 0.0f)
    );

    // 位置を取得する
    Vector2f GetPosition() const;

    // サイズを設定する
    void SetSize(const Vector2f& size);

    // サイズを取得する
    Vector2f GetSize() const;

private:
    Vector2f m_size;
};