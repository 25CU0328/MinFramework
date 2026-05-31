#pragma once

#include "DirectXMath.h"
using namespace DirectX;

#include <vector>

// 頂点データ
struct VertexData
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
};

// メッシュデータ
struct MeshData
{
	std::vector<VertexData> vertexDatas;
	
	// 頂点番号
	std::vector<uint32_t> indices;
};

// モデル全体のデータ
struct ModelData
{
	std::vector<MeshData> meshDatas;
};