#pragma once

#include <vector>
#include <string>

#include "GameObjectData.h"

// シーンのデータを表す構造体
struct SceneData
{
    // ファイルパス
    std::string filePath;
    // シーンの名前
    std::string sceneName;
    // シーンに存在するゲームオブジェクト
    std::vector<GameObjectData> objectDatas;
};

// シリアライズするためのマクロ
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    SceneData,
    filePath,
    sceneName,
    objectDatas
)