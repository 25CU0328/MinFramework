#pragma once

#include "Framework/Math/Vector.h"
#include "Framework/Math/Quaternion.h"

#include <vector>

namespace Runtime
{
	class Transform
	{
	public:
		DirectX::XMMATRIX GetMatrix() const;

		bool IsChild(Transform* _pTransform);

	public:
		void SetParent(Transform* _pTransform);
		Transform* GetParent() const;

		void AddChild(Transform* _pTransform);
		Transform* GetChild(const int _num) const;
	public:
		Vector3f localPosition;
		Quaternion localRotation;
		Vector3f localScale;

		Vector3f worldPosition;
		Quaternion worldRotation;
		Vector3f worldScale;
	protected:
		Transform* m_pParent;
		std::vector<Transform*> m_children;
	};
}