#pragma once

#include <string>
#include "nlohmann/json.hpp"

// シェーダーのアセットデータを受け取るための構造体
struct ShaderData
{
    std::string vertexShaderName;
    std::string pixelShaderName;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    ShaderData,
    vertexShaderName,
    pixelShaderName
)