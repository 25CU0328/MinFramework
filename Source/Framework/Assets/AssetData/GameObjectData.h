#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "Framework/Math/Vector3.h"
#include "Framework/Math/Quaternion.h"
#include "Framework/Assets/AssetData/ComponentData.h"

// ゲームオブジェクトのデータを表す構造体
struct GameObjectData
{
	std::string objectName;
	int objectId;

	std::vector<GameComponentData> componentDatas;

	// 親オブジェクトのID、親がいない場合は-1
	int parentId = -1; 
};

// シリアライズ用のマクロ
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    GameObjectData,
    objectName,
    objectId,
    componentDatas,
    parentId
)