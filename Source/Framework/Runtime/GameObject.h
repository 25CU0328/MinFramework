#pragma once

#include "Framework/Math/Vector.h"
#include "Framework/Math/Quaternion.h"
#include "Framework/Runtime/Transform.h"

#include <string>
#include <vector>

class GameObject
{
public:
	// 初期化処理
	virtual void Init() {}
	// 更新処理
	virtual void Update() {}
	// 描画処理
	virtual void Render() {}
	// 後片付け処理
	virtual void Term() {}
public:
	// オブジェクト名を設定する
	void SetName(std::string _name);
	// オブジェクト名を取得する
	std::string GetName() const;

	// トランスフォームを取得する
	Transform& GetTransform();



protected:
	std::string m_objectName;		// オブジェクト名

	// トランスフォーム
	Transform m_transform;
};
