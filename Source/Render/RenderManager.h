#pragma once

#include "d3d12.h"

// IDXGIFactorを使うためインクルード
#include<dxgi1_6.h>
#pragma comment(lib,"dxgi.lib")

// 描画命令関連の基本コンポーネント
#include "Render/Core/CommandList.h"
#include "Render/Core/CommandQueue.h"
#include "Render/Core/SwapChain.h"
#include "Render/Core/Fence.h"

// パイプライン関連のクラス
#include "Render/Pipeline/RootSignature.h"
#include "Render/Pipeline/PipelineState.h"
#include "Render/Pipeline/ShaderObject.h"

// 
#include "Render/Resource/DescriptorHeap.h"
#include "Render/Resource/DepthStencilBuffer.h"

namespace Render
{
	class RenderManager
	{
		// コピーを禁止する
		RenderManager(const RenderManager&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const RenderManager&) = delete;
	public:
		// コンストラクタ
		RenderManager();
		// デストラクター
		~RenderManager();

		/// <summary>
		/// レンダリングマネージャーの初期化処理
		/// </summary>
		/// <param name="_hwnd"> ウィンドウズの </param>
		
		/// <summary>
		/// レンダリングマネージャーの初期化処理
		/// </summary>
		/// <param name="_hwnd"> ウィンドウズの </param>
		/// <returns> 初期化は成功したか </returns>
		bool Init(const HWND* _hwnd);

		/// <summary>
		/// 現在フレームの描画を開始する
		/// </summary>
		void StartRender();

		/// <summary>
		/// 現在フレームの描画を終わる
		/// </summary>
		void EndRender();

		/// <summary>
		/// デバイスを取得する
		/// </summary>
		/// <returns> デバイスのポインター </returns>
		ID3D12Device* GetDevice();

		/// <summary>
		/// ディスクリプタを取得する
		/// </summary>
		/// <returns> ディスクリプタクラス </returns>
		DescriptorHeap& GetDescriptorHeap();

		ID3D12GraphicsCommandList* GetCommandList();

	private:
		HRESULT _initDevice();
		HRESULT _initBackBuffer();
	private:
		
		ComPtr<ID3D12Device>		m_pDevice;	// デバイス
		IDXGIFactory6*				m_pFactory;	// デバイスを生成するための工場

		Render::CommandList			m_commandList;	// コマンドリスト
		Render::CommandQueue		m_commandQueue;	// コマンドキュー
		Render::SwapChain			m_swapChain;	// スワップチェーン
		Render::Fence				m_fence;		// フェンス

		Render::PipelineState		m_pipelineState;
		Render::RootSignature		m_rootSignature;
		Render::ShaderObject		m_VSObject;		
		Render::ShaderObject		m_PSObject;

		// 定数バッファー・シェーダーリソース用のディスクリプタヒープ
		Render::DescriptorHeap		m_mainHeap;	
		// レンダーターゲットビュー用のディスクリプタヒープ
		Render::DescriptorHeap		m_rtvHeap;	

		D3D12_VIEWPORT				m_viewport;		//ビューポート
		D3D12_RECT					m_scissorRect;		//シザー矩形

		std::vector<ComPtr<ID3D12Resource>> m_backBuffers; 
		UINT						m_backBufferIndex;

		Render::Resource::DepthStencilBuffer m_dsBuffer;
	};
}