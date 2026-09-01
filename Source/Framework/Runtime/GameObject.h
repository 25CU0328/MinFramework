#pragma once

#include "Framework/Runtime/Component/Transform.h"

#include "Framework/Assets/AssetData/GameObjectData.h"
#include "Framework/Runtime/Component/GameComponents.h"

#include <string>
#include <vector>

struct GameObjectData;

class GameObject
{
public:
	// コンストラクタ
	GameObject();
	// デストラクター
	~GameObject();

public:
	// 初期化処理
	virtual void Init();
	virtual void Init(const GameObjectData& _data);
	// 更新処理
	virtual void Update();
	// 描画処理
	virtual void Render();
	// 後片付け処理
	virtual void Term();

public:
	// オブジェクト名を設定する
	void SetName(std::string _name);
	// オブジェクト名を取得する
	std::string GetName() const;

	// オブジェクトIDを設定する
	void SetId(const int _id);
	// オブジェクトIDを取得する
	int GetId() const;

	// コンポーネントを追加する
	void AddComponent(const GameComponentType _type);
	// コンポーネントを取得する
	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			GameComponent* pComponent = m_components[i];
			if (dynamic_cast<T*>(pComponent))
			{
				return dynamic_cast<T*>(pComponent);
			}
		}
		return nullptr;
	}

	// コンポーネントを取得する
	template<typename T>
	const T* GetComponent() const
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			const GameComponent* pComponent = m_components[i];
			if (dynamic_cast<const T*>(pComponent))
			{
				return dynamic_cast<const T*>(pComponent);
			}
		}
		return nullptr;
	}

	// オブジェクトが持っている全てのコンポネントを取得する
	const std::vector<GameComponent*>& GetComponents() const;

	// トランスフォームを取得する
	Transform& GetTransform()
	{
		return *GetComponent<Transform>();
	}
	// トランスフォームを取得する
	const Transform& GetTransform() const
	{
		return *GetComponent<Transform>();
	}

private:
	// コンポネントを生成する
	void _createComponent(const GameComponentData componentData);


protected:
	// オブジェクトID
	int m_objectId;

	// オブジェクト名
	std::string m_objectName;

	// このゲームオブジェクトに所属するコンポーネント
	std::vector<GameComponent*> m_components;
};
