
#include "Scene.h"

// コンストラクタ
Scene::Scene()
	: m_sceneFilePath("")
	, m_sceneName("")
	, m_gameObjects()
{

}

// デストラクター
Scene::~Scene()
{

	
}

// シーンの初期化
void Scene::Init(SceneData _sceneData)
{
	// シーンのファイルパスを設定する
	m_sceneFilePath = _sceneData.filePath;

	// シーン名を設定する
	m_sceneName = _sceneData.sceneName;

	// ゲームオブジェクトを生成する
	for(GameObjectData objectData : _sceneData.objectDatas)
	{
		GameObject* pObject = new GameObject();
		pObject->Init(objectData);

		m_gameObjects.emplace_back(std::move(pObject));
	}

	// 親子関係を設定する
	for (size_t i = 0; i < _sceneData.objectDatas.size(); ++i)
	{
		const auto& data = _sceneData.objectDatas[i];

		if (data.parentId < 0)
			continue;

		GameObject* child = m_gameObjects[i];

		GameObject* parent = m_gameObjects[data.parentId];

		child->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		parent->GetComponent<Transform>()->AddChild(child->GetComponent<Transform>());
	}
}


// シーンの更新処理
void Scene::Update()
{

}

// シーンの描画処理
void Scene::Render()
{
	for(auto pObject : m_gameObjects)
	{
		pObject->Render();
	}
}

// シーンの終了処理
void Scene::Term()
{
	// ゲームオブジェクトの後片付け
	for (auto pObject : m_gameObjects)
	{
		pObject->Term();
		delete pObject;
	}

	m_gameObjects.clear();
}

// シーンのファイルパスを設定する
void  Scene::SetSceneFilePath(const std::string& _filePath)
{
	m_sceneFilePath = _filePath;
}

// シーンのファイルパスを取得する
std::string Scene::GetSceneFilePath() const
{
	return m_sceneFilePath;
}

// シーン名を設定する
void Scene::SetSceneName(const std::string& _sceneName)
{
	m_sceneName = _sceneName;
}

// シーン名を取得する
std::string Scene::GetSceneName() const
{
	return m_sceneName;
}

// ゲームオブジェクトを追加する
void Scene::AddGameObject(GameObject* const _pNewObject)
{
	// nullptrの場合、処理しない
	if (!_pNewObject)
		return;

	// IDが設定されていない場合、処理しない
	if (_pNewObject->GetId() == -1)
		return;

	// 既にシーンに追加されたかを確認する
	auto iterator = std::find(m_gameObjects.begin(), m_gameObjects.end(), _pNewObject);

	if (iterator == m_gameObjects.end())
	{
		m_gameObjects.emplace_back(_pNewObject);
	}
}

// ゲームオブジェクトを削除する
void Scene::DestroyGameObject(GameObject* const _pObject)
{
	// 同じオブジェクトを検索
	auto iterator = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
		[_pObject](const GameObject* pObject)
		{
			return pObject == _pObject;
		}
	);

	// ベクターに存在する場合
	if (iterator != m_gameObjects.end())
	{
		m_gameObjects.erase(iterator);
	}
}

// ゲームオブジェクトをシーム内番号で取得する
GameObject* Scene::GetGameObjectByIndex(int _num)
{
	// ベクターの範囲内であれば取得する
	if (_num >= 0 && _num < (int)(m_gameObjects.size()))
	{
		return m_gameObjects[_num];
	}

	return nullptr;
}

// ゲームのオブジェクトをIDで取得する
GameObject* Scene::GetGameObjectById(const int _id)
{
	// IDで検索する
	auto iterator = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
		[_id](const GameObject* pObject)
		{
			return pObject->GetId() == _id;
		}
	);

	if (iterator != m_gameObjects.end())
	{
		return *iterator;
	}
	return nullptr;
}

// ゲームオブジェクトを名前で取得する
GameObject* Scene::GetGameObjectByName(const std::string& _name)
{
	// 名前で検索する
	auto iterator = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
		[_name](const GameObject* pObject)
		{
			return pObject->GetName() == _name;
		}
	);


	if (iterator != m_gameObjects.end())
	{
		return *iterator;
	}

	return nullptr;
}

// シーンデータを取得する
SceneData Scene::GetSceneData() const
{
	SceneData sceneData;

	// シーンのファイルパスとシーン名を設定する
	sceneData.filePath = m_sceneFilePath;
	sceneData.sceneName = m_sceneName;

	std::vector<GameComponent*> gameComponents;
	// ゲームオブジェクトのデータを取得する
	for (const auto& pObject : m_gameObjects)
	{
		GameObjectData objectData;

		Transform* pTransform = pObject->GetComponent<Transform>();

		objectData.objectName = pObject->GetName();
		objectData.objectId = pObject->GetId();
		objectData.parentId = pTransform->GetParent() ?
			pTransform->GetParent()->GetGameObject()->GetId() : -1;
		
		gameComponents = pObject->GetComponents();
		for (GameComponent* pComponent : gameComponents)
		{
			objectData.componentDatas.emplace_back(pComponent->GetComponentData());
		}

		sceneData.objectDatas.emplace_back(std::move(objectData));
	}

	return sceneData;
}

// シーンにある全てのゲームオブジェクトを取得する
std::vector<GameObject*>& Scene::GetGameObjets()
{
	return m_gameObjects;
}