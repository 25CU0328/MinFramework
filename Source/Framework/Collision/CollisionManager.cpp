
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
			// コライダーの種類は全部バックスの場合
			if (m_colliders[i]->GetColliderType() == ColliderType::Box &&
				m_colliders[j]->GetColliderType() == ColliderType::Box
			)
			{
				// ボックスコライダーの判定を行う
				_checkBoxBox(
					static_cast<BoxCollider*>(m_colliders[i]), 
					static_cast<BoxCollider*>(m_colliders[j])
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
void CollisionManager::_checkBoxBox(BoxCollider* pBox1, BoxCollider* pBox2)
{
	// ポインターはnullptrの場合、処理しない
	if (pBox1 == nullptr || pBox2 == nullptr)
		return;

    Vector2f box1Pos = pBox1->GetPosition();
    Vector2f box1HalfSize = pBox1->GetSize() * 0.5f;

    Vector2f box2Pos = pBox2->GetPosition();
    Vector2f box2HalfSize = pBox2->GetSize() * 0.5f;

	// X座標から見ると重ねたかどうか
	bool isOverlappedX =
		((box1Pos.x - box1HalfSize.x) <= (box2Pos.x + box2HalfSize.x)) &&
		((box1Pos.x + box1HalfSize.x) >= (box2Pos.x - box2HalfSize.x));
	
	// Y座標から見ると重ねたかどうか
	bool isOverlappedY =
		((box1Pos.y - box1HalfSize.y) < (box2Pos.y + box2HalfSize.y)) &&
		((box1Pos.y + box1HalfSize.y) > (box2Pos.y - box2HalfSize.y));

	CollisionEvent event =
	{
		pBox1,
		pBox2
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

		pBox1->OnCollision(event);
		pBox2->OnCollision(event);
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
			pBox1->OnCollision(event);
			pBox2->OnCollision(event);
		}
	}
}

