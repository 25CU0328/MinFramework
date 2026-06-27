#pragma once

#include <string>
#include "nlohmann/json.hpp"

// マテリアルファイルから
// データを受け取るための変数
struct MaterialData
{
    std::string shaderName;
    std::string textureName;

    bool enableZTest;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    MaterialData,
    shaderName,
    textureName,
    enableZTest
)