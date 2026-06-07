#pragma once

#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Render/ComPtr.h"
#include "ShaderByteCode.h"
#include "RootSignature.h"


/*
	描画に使用するシェーダーやレンダリング設定を
	まとめるオブジェクト
*/


namespace Render
{
	class PipelineState
	{
		PipelineState(const PipelineState&) = delete;
		void operator = (const PipelineState&) = delete;

	public:
		PipelineState();
		~PipelineState();

		// 初期化処理
		bool Init(
			ID3D12Device* _pDevice,							
			ShaderByteCode* _pVertexShader,
			ShaderByteCode* _pPixelShader,
			D3D12_INPUT_ELEMENT_DESC _inputElementDescs[],	// 頂点やテクスチャのデータ
			UINT _inputElementNum,							// 上記データの数
			RootSignature* _pRootSignature
		);

		// 後片付け処理
		void Term();

		// パイプラインステートの本体を取得する
		ID3D12PipelineState* Get();

		// 深度テストを行うかどうかを設定する
		void EnableDepthTest(bool _enable);

	private:
		// パイプラインステートの本体
		ComPtr<ID3D12PipelineState> m_pPipelineState;
		// パイプラインの設定情報
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_desc;
	};


}
