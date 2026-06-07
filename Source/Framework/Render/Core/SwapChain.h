#pragma once
#include <d3d12.h>
#include <cstdint>
#include <vector>
#include<dxgi1_6.h>

#include "Render/ComPtr.h"



namespace Render
{
	class SwapChain
	{
		// オブジェクトの複製を禁止する
		SwapChain(const SwapChain&) = delete;
		// オペレーターによるコピーを禁止する
		SwapChain operator = (const SwapChain&) = delete;

	public:
		// コンストラクタ・デストラクター
		SwapChain();
		~SwapChain();

		// 初期化処理
		bool Init(
			IDXGIFactory6* _pFactory,
			IUnknown* _pCommandQueue,
			const HWND* _phwnd
		);

		// 後片付け処理
		void Term();

		// スワップチェーンを取得する
		IDXGISwapChain4* Get();
		// スワップチェーンの設定を取得する
		DXGI_SWAP_CHAIN_DESC GetDesc();
		// 今操作しているバックバッファーの番号を取得する
		UINT GetBackBufferIndex();
	private:
		// スワップチェーンの本体
		ComPtr<IDXGISwapChain4> m_pSwapChain;
	};
}
