
#include "Transform.h"

using namespace Runtime;

void Transform::SetParent(Transform* _pTransform)
{
	m_pParent = _pTransform;
}
Transform* Transform::GetParent() const
{
	return m_pParent;
}

void Transform::AddChild(Transform* _pTransform)
{
	// ヌルポインタの場合、処理しない
	if (_pTransform == nullptr)
		return;

	m_children.emplace_back(_pTransform);
}
Transform* Transform::GetChild(const int _num) const
{
	if (_num > m_children.size())
		return nullptr;

	return m_children[_num];
}