
#include "GameObject.h"

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

// トランスフォームを取得する
Transform& GameObject::GetTransform() 
{
	return m_transform;
}