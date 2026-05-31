
#include "SwapChain.h"
using namespace Render;

#include "AppDef.h"

// コンストラクタ
SwapChain::SwapChain()
{

}

// デストラクター
SwapChain::~SwapChain()
{

}

// 初期化処理
bool SwapChain::Init(
	IDXGIFactory6* _pFactory,
	IUnknown* _pCommandQueue,
	const HWND* _phwnd
)
{
	// スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	{
		swapchainDesc.Width = static_cast<UINT>(WINDOW_WIDTH);
		swapchainDesc.Height = static_cast<UINT>(WINDOW_HEIGHT);
		swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapchainDesc.Stereo = false;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.SampleDesc.Quality = 0;
		swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		swapchainDesc.BufferCount = 2;
		swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	}

	// スワップチェーンの生成
	HRESULT result = _pFactory->CreateSwapChainForHwnd(
		_pCommandQueue,
		*_phwnd,
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)m_pSwapChain.GetAddressOf()
	);

	if (FAILED(result))
	{
		printf("Failed to CreateSwapCain\n");

		return false;
	}


	return true;
}

// 後片付け処理
void SwapChain::Term()
{
	m_pSwapChain.Reset();
}

// IDXGIのスワップチェーンを取得するためのメソッド
IDXGISwapChain4* SwapChain::Get()
{
	return m_pSwapChain.Get();
}

// スワップチェーンの設定を取得する
DXGI_SWAP_CHAIN_DESC SwapChain::GetDesc()
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	HRESULT result = m_pSwapChain->GetDesc(&desc);


	if (FAILED(result))
	{
		printf("【SwapChain】：Failed To Get Desc1");
	}

	return desc;
}

// 今操作しているバックバッファーの番号を取得する
UINT SwapChain::GetBackBufferIndex()
{
	return m_pSwapChain->GetCurrentBackBufferIndex();
}