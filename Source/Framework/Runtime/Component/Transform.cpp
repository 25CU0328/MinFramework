
#include "Transform.h"
// コンストラクタ
Transform::Transform() 
	: m_localPosition(Vector3f(0, 0, 0))
	, m_localRotation(Quaternion::Identity())
	, m_localScale(Vector3f(1, 1, 1))
	, m_pParent(nullptr)
	, m_worldMatrix(DirectX::XMMatrixIdentity())
	, m_children()
	, m_isDirty(true)
{
	m_componentType = GameComponentType::Transform;
}

// デストラクター
Transform::~Transform()
{
	// 子トランスフォームの親をヌルにする
	for (Transform* pChild : m_children)
	{
		pChild->SetParent(nullptr);
	}
}

// 親トランスフォームを設定する
void Transform::SetParent(Transform* pNewParent)
{
	// 親と同じ場合、処理しない
	if(m_pParent == pNewParent)
		return;

	// すでに親がいる場合、親の子供リストから削除する
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	// 新しい親を設定する
	m_pParent = pNewParent;

	// 新しい親がいる場合、親の子供リストに追加する
	if (pNewParent)
	{
		pNewParent->AddChild(this);
	}

	_setDirty();
}

// 親トランスフォームを取得する
Transform* Transform::GetParent() const
{
	return m_pParent;
}


// 子トランスフォームを追加する
void Transform::AddChild(Transform* _pTransform)
{
	// ヌルポインタの場合、処理しない
	if (_pTransform == nullptr)
		return;

	m_children.emplace_back(_pTransform);

	// 子トランスフォームの親を設定する
	_pTransform->SetParent(this);
}

void  Transform::RemoveChild(Transform* _pChild)
{
	// ヌルポインタの場合、処理しない
	if (_pChild == nullptr)
		return;

	// 子供リストから削除する
	auto iterator = std::find(m_children.begin(), m_children.end(), _pChild);
	if (iterator != m_children.end())
	{
		m_children.erase(iterator);
	}
}

// 子供のトランスフォームを取得する
Transform* Transform::GetChild(const int _num) const
{
	if (_num >= m_children.size())
		return nullptr;

	return m_children[_num];
}

// 全ての子供トランスフォームを取得する
const std::vector<Transform*>& Transform::GetChildren() const
{
	return m_children;
}

// 前方向ベクトルを取得する
Vector3f Transform::GetForward() const
{
	return GetWorldRotation().GetForward();
}

// 右方向ベクトルを取得する
Vector3f Transform::GetRight() const
{
	return GetWorldRotation().GetRight();
}

// 上方向ベクトルを取得する
Vector3f Transform::GetUp() const
{
	return GetWorldRotation().GetUp();
}


// ローカル座標を取得する
Vector3f Transform::GetLocalPosition() const
{
	return m_localPosition;
}

// ローカル回転を取得する
Quaternion Transform::GetLocalRotation() const
{
	return m_localRotation;
}

// ローカルスケールを取得する
Vector3f Transform::GetLocalScale() const
{
	return m_localScale;
}


// ローカル座標を設定する
void Transform::SetLocalPosition(const Vector3f& _position)
{
	m_localPosition = _position;

	_setDirty();
}

// ローカル回転を設定する
void Transform::SetLocalRotation(const Quaternion& _rotation)
{
	m_localRotation = _rotation;

	_setDirty();
}

// ローカルスケールを設定する
void Transform::SetLocalScale(const Vector3f& _scale)
{
	m_localScale = _scale;

	_setDirty();
}


// ワールド座標を取得する
Vector3f Transform::GetWorldPosition() const
{
	// ワールド行列を取得する
	const DirectX::XMMATRIX worldMatrix = GetWorldMatrix();

	// ワールド行列からデータを受け取るための変数
	DirectX::XMVECTOR scaleXMVector;
	DirectX::XMVECTOR rotationXMVector;
	DirectX::XMVECTOR translationXMVector;

	// 行列のデータをベクターにコピーする
	DirectX::XMMatrixDecompose(
		&scaleXMVector,
		&rotationXMVector,
		&translationXMVector,
		worldMatrix
	);

	return Vector3f::FromXMVector(translationXMVector);
}

// ワールド回転を取得する
Quaternion Transform::GetWorldRotation() const
{
	// ワールド行列を取得する
	const DirectX::XMMATRIX worldMatrix = GetWorldMatrix();

	// ワールド行列からデータを受け取るための変数
	DirectX::XMVECTOR scaleXMVector;
	DirectX::XMVECTOR rotationXMVector;
	DirectX::XMVECTOR translationXMVector;

	// 行列のデータをベクターにコピーする
	DirectX::XMMatrixDecompose(
		&scaleXMVector,
		&rotationXMVector,
		&translationXMVector,
		worldMatrix
	);

	return {
		DirectX::XMVectorGetX(rotationXMVector),
		DirectX::XMVectorGetY(rotationXMVector),
		DirectX::XMVectorGetZ(rotationXMVector),
		DirectX::XMVectorGetW(rotationXMVector)
	};
}

// ワールドスケールを取得する
Vector3f Transform::GetWorldScale() const
{
	// データを更新する必要がある場合、
	if (m_isDirty)
	{
		_updateWorldData();
	}

	return m_worldScale;
}

// ワールド座標を設定する
void Transform::SetWorldPosition(const Vector3f& _position)
{
	if (!m_pParent)
	{
		SetLocalPosition(_position);
		return;
	}

	// ワールド行列を取得する
	DirectX::XMMATRIX worldMatrix = m_pParent->GetWorldMatrix();

	// ワールド行列の逆行列を算出
	DirectX::XMMATRIX worldInverseMatrix = XMMatrixInverse(
		nullptr,
		worldMatrix
	);

	// ワールド座標をベクターに変換する
	DirectX::XMVECTOR position = Vector3f::ToXMVector(_position);

	// ワールド行列でワールド空間中の位置を算出
	position = XMVector3TransformCoord(position,worldInverseMatrix);

	// ローカル座標を設定する
	SetLocalPosition(Vector3f::FromXMVector(position));

	// 更新が必要と設定する
	_setDirty();
}

// ワールド回転を設定する
void Transform::SetWorldRotation(const Quaternion& _rotation)
{
	if (!m_pParent)
	{
		SetLocalRotation(_rotation);
		return;
	}

	// 親の回転を取得
	Quaternion parentRotation = m_pParent->GetWorldRotation();

	// 親の逆回転でローカル回転を算出
	Quaternion localRotation = parentRotation.GetInverse() * _rotation;

	// ローカル回転を設定する
	SetLocalRotation(localRotation);
}

// ワールドスケールを設定する
void Transform::SetWorldScale(const Vector3f& _newScale)
{
	// 親がない場合、ローカルスケールを返す
	if (!m_pParent)
	{
		SetLocalScale(_newScale);
		return;
	}


	// 親のスケールを取得する
	Vector3f parentScale = m_pParent->GetWorldScale();


	if (std::abs(parentScale.x) < FLT_EPSILON ||
		std::abs(parentScale.y) < FLT_EPSILON ||
		std::abs(parentScale.z) < FLT_EPSILON)
	{

		return;
	}

	// 親のスケールから新しいローカルスケールを算出する
	Vector3f newLocalScale = Vector3f(
		_newScale.x / parentScale.x,
		_newScale.y / parentScale.y,
		_newScale.z / parentScale.z
	);

	// ローカルスケールを設定する
	SetLocalScale(newLocalScale);
}


// 「更新が必要」と設定する
void Transform::_setDirty()
{
	m_isDirty = true;

	for (auto childTransform : m_children)
	{
		childTransform->_setDirty();
	}
}

// ワールド行列を取得する
DirectX::XMMATRIX Transform::GetWorldMatrix() const
{
	if (m_isDirty)
	{
		_updateWorldData();
	}

	return m_worldMatrix;
}

// トランスフォームのコンポネントデータを取得する
GameComponentData Transform::GetComponentData() const
{
	// トランスフォームデータを作成する
	TransformData transformData;
	{
		transformData.position	= m_localPosition;
		transformData.rotation	= m_localRotation;
		transformData.scale		= m_localScale;
	}

	GameComponentData componentData;
	{
		componentData.type = m_componentType;
		componentData.data = transformData;
	}

	return componentData;
}

// コンポネントを設定する
void Transform::SetComponent(const GameComponentData _componentData)
{
	TransformData data = _componentData.data.get<TransformData>();

	SetLocalPosition(data.position);
	SetLocalRotation(data.rotation);
	SetLocalScale(data.scale);
}

// ワールド行列などのデータを更新する
void Transform::_updateWorldData() const
{
	// ローカルの行列を取得する
	DirectX::XMMATRIX localMatrix = _getLocalMatrix();

	// 親の有無による行列を更新する
	DirectX::XMMATRIX worldMatrix = m_pParent ? 
		localMatrix * m_pParent->GetWorldMatrix() : localMatrix;
	
	// ワールド行列からデータを受け取るための変数
	DirectX::XMVECTOR scaleXMVector;
	DirectX::XMVECTOR rotationXMVector;
	DirectX::XMVECTOR translationXMVector;
	
	// 行列のデータをベクターにコピーする
	DirectX::XMMatrixDecompose(
		&scaleXMVector,
		&rotationXMVector,
		&translationXMVector,
		worldMatrix
	);

	// ワールド座標、ワールド回転、ワールドスケールを更新する
	m_worldPosition = Vector3f::FromXMVector(translationXMVector);
	m_worldRotation = Quaternion::FromXMVector(rotationXMVector);
	m_worldScale = Vector3f::FromXMVector(scaleXMVector);

	// ワールド行列を更新する
	m_worldMatrix = worldMatrix;

	// 更新完了と設定する
	m_isDirty = false;
}

// 行列を取得する
DirectX::XMMATRIX Transform::_getLocalMatrix() const
{
	// スケーリング行列
	DirectX::XMMATRIX scaleMatrix = DirectX::XMMatrixScalingFromVector(
		Vector3f::ToXMVector(m_localScale)
	);

	// 回転行列
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(
		Quaternion::ToXMVector(m_localRotation)
	);

	// 平行移動行列
	DirectX::XMMATRIX translateMatrix = DirectX::XMMatrixTranslationFromVector(
		Vector3f::ToXMVector(m_localPosition)
	);

	return scaleMatrix * rotationMatrix * translateMatrix;
}