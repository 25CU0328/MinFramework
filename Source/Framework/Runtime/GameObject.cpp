
#include "GameObject.h"
#include "Framework/Runtime/Component/GameComponentFactory.h"

// コンストラクタ
GameObject::GameObject()
	: m_objectId(-1)
	, m_objectName("")
	, m_components()
{

}

// デストラクター
GameObject::~GameObject()
{

}

void GameObject::Init()
{
	AddComponent(GameComponentType::Transform);
}

void GameObject::Init(const GameObjectData& _data)
{
	m_objectId = _data.objectId;
	m_objectName = _data.objectName;

	for (GameComponentData componentData : _data.componentDatas)
	{
		_createComponent(componentData);
	}
}

// 更新処理
void GameObject::Update()
{
	for (GameComponent* pComponent : m_components)
	{
		pComponent->Update();
	}
}

// 描画処理
void GameObject::Render()
{
	for (GameComponent* pComponent : m_components)
	{
		pComponent->Render();
	}
}

// 後片付け処理
void GameObject::Term()
{
	for (GameComponent* pComponent : m_components)
	{
		pComponent->Term();
	}

	m_components.clear();
}

// オブジェクト名を設定する
void GameObject::SetName(std::string _name)
{
	m_objectName = _name;
}
// オブジェクト名を取得する
std::string GameObject::GetName() const
{
	return m_objectName;
}

// オブジェクトIDを設定する
void GameObject::SetId(const int _id)
{
	m_objectId = _id;
}

// オブジェクトIDを取得する
int GameObject::GetId() const
{
	return m_objectId;
}

// コンポーネントを追加する
void GameObject::AddComponent(const GameComponentType _type)
{
	// コンポーネントを生成する
	GameComponent* pComponent = GameComponentFactory::CreateComponent(_type);
	
	if (pComponent)
	{
		// 所属するコンポーネントのリストに追加する	
		m_components.emplace_back(std::move(pComponent));

		// コンポネントの初期化を行う
		m_components.back()->Init(this);
	}
}

// オブジェクトが持っている全てのコンポネントを取得する
const std::vector<GameComponent*>& GameObject::GetComponents() const
{
	return m_components;
}

// コンポネントを生成する
void GameObject::_createComponent(const GameComponentData _componentData)
{
	switch (_componentData.type)
	{
	case GameComponentType::Transform:
		m_components.emplace_back(new Transform());
		break;

	case GameComponentType::MeshRenderer:
		m_components.emplace_back(new MeshRenderer());
		break;

	case GameComponentType::TextureRenderer:
		m_components.emplace_back(new TextureRenderer());
		break;
	}

	m_components.back()->Init(this);
	m_components.back()->SetComponent(_componentData);
}