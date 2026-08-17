

#include "Shader.h"
#include "Framework/Framework.h"

// 初期化処理
bool Shader::Init(ShaderData _shaderData)
{
	if (_shaderData.pixelShaderName == "" || _shaderData.vertexShaderName == "")
	{
		printf("[Shader]：ShaderName is Enmty\n");
		return false;
	}

	std::wstring tempWstring = std::wstring(_shaderData.vertexShaderName.begin(), _shaderData.vertexShaderName.end());
	if (!m_vsByteCode.Init(tempWstring.c_str(), Render::ShaderType::VertexShader))
	{
		printf("[Shader]：Failed to Initialize Vertex Shader\n");
		return false;
	}

	tempWstring = std::wstring(_shaderData.pixelShaderName.begin(), _shaderData.pixelShaderName.end());
	if (!m_psByteCode.Init(tempWstring.c_str(), Render::ShaderType::PixelShader))
	{
		printf("[Shader]：Failed to Initialize Pixel Shader\n");
		return false;
	}

	if (!m_rootSignature.Init(UINT(2)))
	{
		printf("[Shader]：Failed to Initialize RootSignature");
		return false;
	}


	// ヴァーテックスシェーダーのインプットを定義する
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		// 今回追加されたUV項目
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};
	if (!m_pipelineState.Init(
		Render_I->GetGraphics()->GetDevice(),
		&m_vsByteCode,
		&m_psByteCode,
		inputLayout,
		_countof(inputLayout),
		&m_rootSignature
	))
	{
		printf("[Shader]：Failed to Initialize pipelineState");
		return false;
	}

	return true;
}

// ルートシグネチャーを取得する
ID3D12RootSignature* Shader::GetRootSignature()
{
	return m_rootSignature.Get();
}

// パイプラインステートを取得する
ID3D12PipelineState* Shader::GetPipelineState()
{
	return m_pipelineState.Get();
}