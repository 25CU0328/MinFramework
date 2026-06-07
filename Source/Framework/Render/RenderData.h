#pragma once

#include "d3d12.h"
#include "DirectXMath.h"
#include "Framework/Render/Resource/ConstantBuffer.h"
#include "Framework/Runtime/Material.h"

struct RenderData
{
	// ヴァーテックスバッファーの設定
	D3D12_VERTEX_BUFFER_VIEW	vertexBufferView;
	// インデックスバッファーの設定
	D3D12_INDEX_BUFFER_VIEW		indexBufferView;
	// インデックス数
	UINT						indexNum;
	// 使用するコンスタントバッファーのポインター
	Render::ConstantBuffer*		pConstantBuffer;

	// 使用するマテリアルのポインター
	Runtime::Material*			pMaterial;
};