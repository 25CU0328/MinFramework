
#pragma once

#include <string>
#include "Framework/Math/Quaternion.h"
#include "Framework/Math/Vector3.h"

#include "Framework/Runtime/Component/ComponentType.h"
#include "nlohmann/json.hpp"

// コンポネントデータのベースクラス
struct GameComponentData
{
	GameComponentType type;
	nlohmann::json data;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
	GameComponentData,
	type,
	data
)

struct MeshRendererData
{
	std::string meshFilePath;
	std::string materialPath;
	std::string textureFilePath;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
	MeshRendererData,
	meshFilePath,
	materialPath,
	textureFilePath
)

struct TextureRendererData
{
	std::string textureFilePath;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
	TextureRendererData,
	textureFilePath
)


// ゲームオブジェクトのトランスフォームデータを表す構造体
struct TransformData
{
	Vector3f position;
	Quaternion rotation;
	Vector3f scale;
};

// シリアライズ用のマクロ
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
	TransformData,
	position,
	rotation,
	scale
)