
#pragma once
class Collider;

// 衝突の種類
enum CollisionEventType
{
	Enter,
	Stay,
	Exit,
};

// 衝突のイベント
struct CollisionEvent
{
	Collider* pColliderA;
	Collider* pColliderB;
	// 衝突の種類
	CollisionEventType type;
	bool operator==(const CollisionEvent& otherEvent) const
	{
		return
			(pColliderA == otherEvent.pColliderA && pColliderB == otherEvent.pColliderB) ||
			(pColliderA == otherEvent.pColliderB && pColliderB == otherEvent.pColliderA);
	}
};