#pragma once

#include <DirectXTex.h>


struct ImageData
{
	DirectX::TexMetadata metaData;
	const DirectX::Image* image;
};