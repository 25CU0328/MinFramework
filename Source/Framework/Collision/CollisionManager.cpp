
#include "CollisionManager.h"

// コンストラクタ
CollisionManager::CollisionManager()
{

}
// デストラクター
CollisionManager::~CollisionManager()
{

}

// 更新処理
void CollisionManager::Update()
{
	// 今フレームの衝突結果を前フレームにコピーする
	m_previousCollisions = std::move(m_currentCollisions);
	m_currentCollisions.clear();


	for (int i = 0; i < m_colliders.size(); ++i)
	{
		for (int j = i+1; j < m_colliders.size(); ++j)
		{

			int iLayer = m_colliders[i]->GetLayer();
			int iHitLayer = m_colliders[i]->GetHitLayer();

			int jLayer = m_colliders[j]->GetLayer();
			int jHitLayer = m_colliders[j]->GetHitLayer();

			// レイヤーが衝突レイヤーの設定に含まれない場合、処理しない
			if (!(iLayer & jHitLayer || jLayer & iHitLayer))
				continue;

			// コライダーの種類は全部バックスの場合
			if (m_colliders[i]->GetColliderType() == ColliderType::Rect &&
				m_colliders[j]->GetColliderType() == ColliderType::Rect
			)
			{
				// ボックスコライダーの判定を行う
				_checkRectRect(
					static_cast<RectCollider*>(m_colliders[i]),
					static_cast<RectCollider*>(m_colliders[j])
				);
			}
		}
	}
}

// コライダーの登録
void CollisionManager::Register(Collider* _pCollider)
{
	auto iterator = std::find(m_colliders.begin(), m_colliders.end(), _pCollider);

	// もし既に登録されたら、処理しない
	if (iterator != m_colliders.end())
		return;

	// そうじゃない場合、登録する
	m_colliders.push_back(_pCollider);
}

// 登録されたコライダーの削除
void CollisionManager::Unregister(Collider* _pCollider)
{
	auto iterator = std::find(m_colliders.begin(), m_colliders.end(), _pCollider);

	// まだ登録されていない場合、処理しない
	if (iterator == m_colliders.end())
		return;

	// vectorから削除
	m_colliders.erase(iterator);
}

// 二つのボックスコライダーの衝突を判定する
void CollisionManager::_checkRectRect(RectCollider* pRect1, RectCollider* pRect2)
{
	// ポインターはnullptrの場合、処理しない
	if (pRect1 == nullptr || pRect2 == nullptr)
		return;

    Vector2f rect1Pos = pRect1->GetPosition();
    Vector2f rect1HalfSize = pRect1->GetSize() * 0.5f;

    Vector2f rect2Pos = pRect2->GetPosition();
    Vector2f rect2HalfSize = pRect2->GetSize() * 0.5f;

	// X座標から見ると重ねたかどうか
	bool isOverlappedX =
		((rect1Pos.x - rect1HalfSize.x) <= (rect2Pos.x + rect2HalfSize.x)) &&
		((rect1Pos.x + rect1HalfSize.x) >= (rect2Pos.x - rect2HalfSize.x));
	
	// Y座標から見ると重ねたかどうか
	bool isOverlappedY =
		((rect1Pos.y - rect1HalfSize.y) < (rect2Pos.y + rect2HalfSize.y)) &&
		((rect1Pos.y + rect1HalfSize.y) > (rect2Pos.y - rect2HalfSize.y));

	// 
	CollisionEvent event =
	{
		pRect1,
		pRect2
	};
	
	// もしX座標とY座標から見ても重なっていたら
	// 衝突発生と判定する
	if (isOverlappedX && isOverlappedY)
	{
		auto iterator = std::find(
			m_previousCollisions.begin(),
			m_previousCollisions.end(),
			event
		);

		// 前回の記録に存在する場合、Exitと設定する
		if (iterator != m_previousCollisions.end())
		{
			event.type = CollisionEventType::Stay;
		}
		// そうじゃない場合、Enterと設定する
		else
		{
			event.type = CollisionEventType::Enter;
		}

		// ベクターに保存する
		m_currentCollisions.emplace_back(event);

		pRect1->OnCollision(event);
		pRect2->OnCollision(event);
	}
	// 衝突が発生していない場合、前回の記録をチェック
	else
	{
		auto iterator = std::find(
			m_previousCollisions.begin(),
			m_previousCollisions.end(),
			event
		);

		// 前回の記録に存在する場合、Exitと設定する
		if (iterator != m_previousCollisions.end())
		{
			event.type = CollisionEventType::Exit;

			// Exitのためベクターに保存しない
			pRect1->OnCollision(event);
			pRect2->OnCollision(event);
		}
	}
}

