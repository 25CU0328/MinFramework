
#include "PipelineState.h"

using namespace Render;

PipelineState::PipelineState()
{

}

PipelineState::~PipelineState()
{

}

// 初期化処理
bool PipelineState::Init(
	ID3D12Device* _pDevice,
	ShaderObject* _pVertexShader,
	ShaderObject* _pPixelShader,
	D3D12_INPUT_ELEMENT_DESC _inputElementDescs[],
	UINT _inputElementNum,
	RootSignature* _pRootSignature
)
{
	// パイプラインステートの設定情報
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};

	// シェーダーの設定
	pipelineDesc.VS.pShaderBytecode = _pVertexShader->GetShaderByteCode();
	pipelineDesc.VS.BytecodeLength = _pVertexShader->GetShaderByteCodeLength();
	pipelineDesc.PS.pShaderBytecode = _pPixelShader->GetShaderByteCode();
	pipelineDesc.PS.BytecodeLength = _pPixelShader->GetShaderByteCodeLength();

	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//中身は0xffffffff

	// ブランド設定
	pipelineDesc.BlendState.AlphaToCoverageEnable = false;
	pipelineDesc.BlendState.IndependentBlendEnable = false;

	// レンダーターゲットのブランド設定
	D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
	{
		//ひとまず加算や乗算やαブレンディングは使用しない
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//ひとまず論理演算は使用しない
		renderTargetBlendDesc.LogicOpEnable = false;
	}
	pipelineDesc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

	// ラストライザ設定
	D3D12_RASTERIZER_DESC rasterizerDesc = {};
	{
		rasterizerDesc.MultisampleEnable = false;//まだアンチェリは使わない
		rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;//カリングしない
		rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;//中身を塗りつぶす
		rasterizerDesc.DepthClipEnable = true;//深度方向のクリッピングは有効に

		// 三角形の頂点データは時計回りかどうか
		rasterizerDesc.FrontCounterClockwise = false;
		// デプススバッファーに関する設定
		rasterizerDesc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		rasterizerDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		rasterizerDesc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;

		// Anti-Alias関連
		rasterizerDesc.MultisampleEnable = false;		
		rasterizerDesc.AntialiasedLineEnable = false;

		// 強制に設定するサンプリング
		rasterizerDesc.ForcedSampleCount = 0;			

		rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	}
	pipelineDesc.RasterizerState = rasterizerDesc;

	// デプスステンシルの設定
	D3D12_DEPTH_STENCIL_DESC depthDesc = {};
	{
		// 暫くTRUEにする
		depthDesc.DepthEnable = true;
		depthDesc.StencilEnable = false;

		depthDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		depthDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	}
	pipelineDesc.DepthStencilState = depthDesc;

	pipelineDesc.InputLayout.pInputElementDescs = _inputElementDescs;	//レイアウト先頭アドレス
	pipelineDesc.InputLayout.NumElements = _inputElementNum;			//レイアウト配列数

	//ストリップ時のカットなし
	pipelineDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形で構成

	//今は１つのみ
	pipelineDesc.NumRenderTargets = 1;
	//0～1に正規化されたRGBA
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	pipelineDesc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
	pipelineDesc.SampleDesc.Quality = 0;//クオリティは最低

	pipelineDesc.pRootSignature = _pRootSignature->Get();

	// パイプラインステートの生成
	HRESULT result = _pDevice->CreateGraphicsPipelineState(
		&pipelineDesc, 
		IID_PPV_ARGS(m_pPipelineState.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("【PipelineState】：Failed to Create GraphicPipelineState\n");

		return false;
	}

	return true;
}



// 後片付け処理
void PipelineState::Term()
{
	m_pPipelineState->Release();
}

// パイプラインステートの本体を取得する
ID3D12PipelineState* PipelineState::Get()
{
	return m_pPipelineState.Get();
}