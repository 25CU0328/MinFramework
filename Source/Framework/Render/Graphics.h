#pragma once

#include "d3d12.h"
// IDXGIFactorを使うためインクルード
#include<dxgi1_6.h>

// 描画命令関連の基本コンポーネント
#include "Framework/Render/Core/CommandList.h"
#include "Framework/Render/Core/CommandQueue.h"
#include "Framework/Render/Core/SwapChain.h"
#include "Framework/Render/Core/Fence.h"

// パイプライン関連のクラス
#include "Framework/Render/Pipeline/RootSignature.h"
#include "Framework/Render/Pipeline/PipelineState.h"
#include "Framework/Render/Pipeline/ShaderByteCode.h"

// 
#include "Framework/Render/Resource/DescriptorHeap.h"
#include "Framework/Render/Resource/DepthStencilBuffer.h"

namespace Render
{
	class Graphics
	{
		// コピーを禁止する
		Graphics(const Graphics&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const Graphics&) = delete;
	public:
		// コンストラクタ
		Graphics();
		// デストラクター
		~Graphics();

		/// <summary>
		/// レンダリングマネージャーの初期化処理
		/// </summary>
		/// <param name="_hwnd"> ウィンドウのハンドル </param>
		/// <returns> 初期化は成功したか </returns>
		bool Init(HWND* _hwnd);

		// 現在フレームの描画を開始する
		void BeginFrame();

		// 現在フレームの描画を終わる
		void EndFrame();

		// デバイスを取得する
		ID3D12Device* GetDevice();

		// ディスクリプタを取得する
		DescriptorHeap& GetDescriptorHeap();

		// コマンドリストを取得する
		ID3D12GraphicsCommandList* GetCommandList();

		// コマンドキューを取得する
		ID3D12CommandQueue* GetCommandQueue();

		// ウィンドウハンドルを取得する
		HWND* GetHWND();
	private:
		HRESULT _initDevice();
		HRESULT _initBackBuffer();
	private:

		ComPtr<ID3D12Device>		m_pDevice;	// デバイス
		IDXGIFactory6* m_pFactory;	// デバイスを生成するための工場

		HWND* m_pHwnd;								// ウィンドウのハンドル

		Render::CommandList			m_commandList;	// コマンドリスト
		Render::CommandQueue		m_commandQueue;	// コマンドキュー
		Render::SwapChain			m_swapChain;	// スワップチェーン
		Render::Fence				m_fence;		// フェンス

		Render::PipelineState		m_pipelineState;
		Render::RootSignature		m_rootSignature;
		Render::ShaderByteCode		m_VSByteCode;
		Render::ShaderByteCode		m_PSByteCode;

		// 定数バッファー・シェーダーリソース用のディスクリプタヒープ
		Render::DescriptorHeap		m_mainHeap;
		// レンダーターゲットビュー用のディスクリプタヒープ
		Render::DescriptorHeap		m_rtvHeap;

		D3D12_VIEWPORT				m_viewport;		//ビューポート
		D3D12_RECT					m_scissorRect;	//シザー矩形

		// バックバッファー
		std::vector<ComPtr<ID3D12Resource>> m_backBuffers;
		UINT						m_backBufferIndex;

		// 深度とステンシルバッファー
		Render::Resource::DepthStencilBuffer m_dsBuffer;
	};
}