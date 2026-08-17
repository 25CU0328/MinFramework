#pragma once

#include "Framework/Assets/AssetData/ShaderData.h"

#include "Framework/Render/Pipeline/ShaderByteCode.h"
#include "Framework/Render/Pipeline/RootSignature.h"
#include "Framework/Render/Pipeline/PipelineState.h"

#include <d3d12.h>


class Shader
{
public:
	// 初期化処理
	bool Init(ShaderData _shaderData);

	// ルートシグネチャーを取得する
	ID3D12RootSignature* GetRootSignature();

	// パイプラインステートを取得する
	ID3D12PipelineState* GetPipelineState();

private:
	Render::ShaderByteCode m_vsByteCode;
	Render::ShaderByteCode m_psByteCode;

	Render::RootSignature m_rootSignature;
	Render::PipelineState m_pipelineState;
};
