#pragma once

#include <string>
#include "nlohmann/json.hpp"

struct MaterialAsset
{
	std::string shaderName;
	std::string textureName;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    MaterialAsset,
    shaderName,
    textureName
)