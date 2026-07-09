#pragma once

#include <functional>
#include "ColliderType.h"
#include "Framework/Collision/CollisionEvent.h"
// 全てのコライダーのベースクラス
class Collider
{
public:
	virtual ~Collider() = default;
	virtual void OnCollision(CollisionEvent _collisionEvent)
	{
		if (m_collisionCallback)
		{
			m_collisionCallback(_collisionEvent);
		}
	}

    // コライダーの種類を取得する
    ColliderType GetColliderType() const
    {
        return m_type;
    }

    // コールバック関数を設定する
    void SetCallback(std::function<void(CollisionEvent)> _callback)
    {
        m_collisionCallback = _callback;
    }

protected:
	std::function<void(CollisionEvent)> m_collisionCallback;
    ColliderType m_type;
};