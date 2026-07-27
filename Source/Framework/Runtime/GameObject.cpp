
#include "GameObject.h"

using namespace Runtime;


// 位置を設定する
void GameObject::SetPosition(const Vector2f& _position)
{
	m_position = Vector3f(_position.x, _position.y, 0.0f);
}

// 位置を設定
void GameObject::SetPosition(const Vector3f& _position)
{
	m_position = _position;
}

// 位置を取得する
Vector3f GameObject::GetPosition() const
{
	return m_position;
}


// 回転を設定する
void GameObject::SetRotation(const Quaternion& _rotation)
{
	m_rotation = _rotation;
}

// 回転を設定する
void GameObject::SetRotationEuler(const Vector3f& _rotation)
{
	m_rotation = Quaternion::FromEuler(_rotation);
}

// 回転を取得する
Quaternion GameObject::GetRotation() const
{
	return m_rotation;
}

// 回転を取得する
Vector3f GameObject::GetRotationEuler() const
{
	return m_rotation.ToEuler();
}


// スケールを設定する
void GameObject::SetScale(const Vector3f& _scale)
{
	m_scale = _scale;
}

// スケールを取得する
Vector3f GameObject::GetScale() const
{
	return m_scale;
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