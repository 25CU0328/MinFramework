
#include "GameComponent.h"

// コンストラクタ
GameComponent::GameComponent()
	: m_pOwnerObject(nullptr)
	, m_componentType(GameComponentType::None)
{

}

// デストラクター
GameComponent::~GameComponent() 
{

}

// 初期化処理
void GameComponent::Init(GameObject* const _pOwnerObject) 
{
	m_pOwnerObject = _pOwnerObject;
}

// 更新処理
void GameComponent::Update() {}
// 描画処理
void GameComponent::Render() {}
// 後片付け処理
void GameComponent::Term() {}

// コンポネントの種類を取得する
GameComponentType GameComponent::GetComponentType() const
{ 
	return m_componentType; 
}

// コンポネントと結びつけるゲームオブジェクトを取得する
GameObject* GameComponent::GetGameObject() const
{
	return m_pOwnerObject;
}
