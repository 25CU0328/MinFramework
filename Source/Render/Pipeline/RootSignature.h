#pragma once

#include <d3d12.h>

#include "Render/ComPtr.h"


/*
	シェーダーが使用するリソース(バッファー)を定義するクラス

	※シェーダーとバッファーのバインドはRenderManagerで設定します
	ただし、実際のバインドはコマンドリストに入れた命令によって行われます
	そのため、RootSignatureの設定が正しくても、バインド処理のミスによる不具合
	が発生する場合もあります。
*/

namespace Render
{
	class RootSignature
	{
		RootSignature(const RootSignature&) = delete;
		void operator = (const RootSignature&) = delete;

	public:
		RootSignature();
		~RootSignature();

		// 初期化処理
		bool Init(UINT _samplerNum);
		// 後片付け処理
		void Term();

		// ルートシグネチャーの本体を取得
		ID3D12RootSignature* Get() const;
	private:
		// ルートシグネチャの本体
		ComPtr<ID3D12RootSignature> m_pRootSignature; 
	};


}
