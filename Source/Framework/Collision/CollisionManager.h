#pragma once

#include "CollisionEvent.h"
#include "Collider/BoxCollider.h"
#include <vector>

class CollisionManager
{
	// コピーを禁止する
	CollisionManager(const CollisionManager&) = delete;
	// オペレーターによるコピーを禁止する
	void operator = (const CollisionManager&) = delete;
public:
	

	// コンストラクタ
	CollisionManager();
	// デストラクター
	~CollisionManager();

	// 更新処理
	void Update();
	// コライダーの登録
	void Register(Collider* _pCollider);
	// 登録されたコライダーの削除
	void Unregister(Collider* _pCollider);
	
private:
	// 二つのボックスコライダーの衝突を判定する
	void _checkBoxBox(BoxCollider* pBox1, BoxCollider* pBox2);

private:
	std::vector<Collider*> m_colliders;

	std::vector<CollisionEvent> m_currentCollisions;
	std::vector<CollisionEvent> m_previousCollisions;
};