#pragma once

#include "ComponentType.h"
#include "Framework/Assets/AssetData/ComponentData.h"

class GameObject; // 前方宣言

// コンポーネントの基底クラス
class GameComponent
{
public:
	// コンストラクタ
	GameComponent();
	// デストラクター
	~GameComponent();

public:
	// 初期化処理
	virtual void Init(GameObject* const _pOwnerObject);
	// 更新処理
	virtual void Update();
	// 描画処理
	virtual void Render();
	// 後片付け処理
	virtual void Term();

	// コンポネントデータを取得する
	virtual GameComponentData GetComponentData() const = 0;

	// コンポネントデータでコンポネントを設定する
	virtual void SetComponent(const GameComponentData _componentData) = 0;

	// コンポネントの種類を取得する
	GameComponentType GetComponentType() const;

	// コンポネントと結びつけるゲームオブジェクトを取得する
	GameObject* GetGameObject() const;

protected:
	// 所属するゲームオブジェクト
	GameObject* m_pOwnerObject;	
	// コンポーネントの種類
	GameComponentType m_componentType;	
};