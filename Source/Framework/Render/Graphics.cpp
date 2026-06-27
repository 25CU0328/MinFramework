
#include "Graphics.h"
using namespace Render;

#include "AppDef.h"

// コンストラクタ
Graphics::Graphics()
	: m_pDevice()
	, m_pFactory()
	, m_commandList()
	, m_commandQueue()
	, m_swapChain()
	, m_fence()
	, m_rootSignature()
	, m_pipelineState()
	, m_viewport()
	, m_scissorRect()
	, m_backBuffers()
	, m_backBufferIndex(0)
	, m_dsBuffer()
{

}
// デストラクター
Graphics::~Graphics()
{

}

/// <summary>
/// レンダリングマネージャーの初期化処理
/// </summary>
/// <param name="_hwnd"> ウィンドウズの </param>

bool Graphics::Init(const HWND* _pHwnd)
{
	HRESULT result = _initDevice();
	if (FAILED(result))
	{
		printf("【RenderManager】：Failed to Initilize ID3DDevice\n");
		return false;
	}

	// コマンドリストの初期化
	// スクリーンが二つあるため、バッファーも二つで設定する
	if (!m_commandList.Init(m_pDevice.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT, 2))
		return false;

	// コマンドキューの初期化
	if (!m_commandQueue.Init(m_pDevice.Get()))
		return false;

	// スワップチェーンの初期化
	if (!m_swapChain.Init(m_pFactory, m_commandQueue.Get(), _pHwnd))
		return false;

	// --------------------------
	// レンダーターゲットビュー
	// --------------------------
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビューなので当然RTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;//表裏の２つ
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//特に指定なし
	ID3D12DescriptorHeap* rtvHeaps = nullptr;
	result = m_pDevice.Get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));

	if (!m_fence.Init(m_pDevice.Get()))
		return false;

	if (!m_rtvHeap.Init(
		m_pDevice.Get(),
		D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
		D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
		2
	))
	{
		return false;
	}

	// 定数バッファー・シェーダーリソース用のディスクリプタヒープ
	if (!m_mainHeap.Init(
		m_pDevice.Get(),
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		2
	))
	{
		return false;
	}

	result = _initBackBuffer();
	if (FAILED(result))
	{
		printf("【RenderManager】：Failed to Init Backbuffer\n");
		return false;
	}
	if (!m_dsBuffer.Init(m_pDevice.Get()))
	{
		return false;
	}

	// ヴァーテックスシェーダーバイトコードの生成
	if (!m_VSByteCode.Init(
		L"Assets/Shader/VertexShader.hlsl",
		ShaderType::VertexShader
	))
	{
		printf("Failed to Create VertexShader\n");
		return false;
	}

	// ピクセルシェーダーのバイトコードの生成
	if (!m_PSByteCode.Init(
		L"Assets/Shader/PixelShader.hlsl",
		ShaderType::PixelShader
	))
	{
		printf("Failed to Create PixelShader\n");
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

	if (!m_rootSignature.Init(1))
	{
		return false;
	}

	if (!m_pipelineState.Init(
		m_pDevice.Get(),
		&m_VSByteCode,
		&m_PSByteCode,
		inputLayout,
		_countof(inputLayout),
		&m_rootSignature
	))
	{
		return false;
	}

	// -------------------
	// ビューポート
	// -------------------
	m_viewport.Width = static_cast<FLOAT>(WINDOW_WIDTH);//出力先の幅(ピクセル数)
	m_viewport.Height = static_cast<FLOAT>(WINDOW_HEIGHT);//出力先の高さ(ピクセル数)
	m_viewport.TopLeftX = 0;//出力先の左上座標X
	m_viewport.TopLeftY = 0;//出力先の左上座標Y
	m_viewport.MaxDepth = 1.0f;//深度最大値
	m_viewport.MinDepth = 0.0f;//深度最小値

	// -------------------
	// シザー矩形
	// -------------------
	m_scissorRect.top = 0;//切り抜き上座標
	m_scissorRect.left = 0;//切り抜き左座標
	m_scissorRect.right = m_scissorRect.left + static_cast<LONG>(WINDOW_WIDTH);//切り抜き右座標
	m_scissorRect.bottom = m_scissorRect.top + static_cast<LONG>(WINDOW_HEIGHT);//切り抜き下座標

	m_backBufferIndex = 0;

	return true;
}

// 現在フレームの描画を開始する
void Graphics::BeginFrame()
{
	// 頻繫に使われるため一時的な変数に保存する
	ID3D12GraphicsCommandList* pCommandList = m_commandList.Get();

	m_backBufferIndex = m_swapChain.GetBackBufferIndex();
	m_commandList.Reset(m_backBufferIndex);

	//リソースバリアの設定
	{
		//コマンド積み始めるための設定
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = m_backBuffers[m_backBufferIndex].Get();
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		//リソースバリア
		pCommandList->ResourceBarrier(1, &barrier);
	}

	//レンダーターゲットを指定
	D3D12_CPU_DESCRIPTOR_HANDLE pCPUHandle = m_rtvHeap.GetCPUHeapHandle();

	UINT allocateSize = m_backBufferIndex * m_pDevice.Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	pCPUHandle.ptr += allocateSize;

	// デプスステンシルの位置を取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_dsBuffer.GetHandle();

	// 出力統合段階の描画対象を設定
	pCommandList->OMSetRenderTargets(1, &pCPUHandle, false, &dsvHandle);

	// デプスステンシル値のリセット
	pCommandList->ClearDepthStencilView(
		dsvHandle,
		D3D12_CLEAR_FLAG_DEPTH,
		1.0f,
		0,
		0,
		nullptr
	);

	float clearColor[] = { 0.1f, 0.2f, 0.4f, 1.0f };
	pCommandList->ClearRenderTargetView(
		pCPUHandle,
		clearColor,
		0,
		nullptr
	);

	// ビューポートとシザー矩形の設定
	pCommandList->RSSetViewports(1, &m_viewport);
	pCommandList->RSSetScissorRects(1, &m_scissorRect);

	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ディスクリプタヒープの指定
	ID3D12DescriptorHeap* pDescriptorHeap = m_mainHeap.Get();
	pCommandList->SetDescriptorHeaps(1, &pDescriptorHeap);
}

// 現在フレームの描画を終わる
void Graphics::EndFrame()
{
	ID3D12GraphicsCommandList* pCommandList = m_commandList.Get();

	//リソースバリアの設定
	{
		//コマンド積み終わったのでGPUに描画させるように設定する
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = m_backBuffers[m_backBufferIndex].Get();
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		//リソースバリア
		pCommandList->ResourceBarrier(1, &barrier);
	}

	//命令のクローズ
	pCommandList->Close();


	// コマンドキューに渡すため、配列として再作成
	ID3D12CommandList* cmdlists[] = { pCommandList };
	//コマンドリストの実行
	m_commandQueue.Execute(_countof(cmdlists), cmdlists);

	// フリップ
	m_swapChain.Get()->Present(1, 0);

	// GPUと同期する
	// GPUの処理が終わるまで待つ
	m_fence.SynAndWait(m_commandQueue.Get(), INFINITE);
}

// デバイスの初期化処理
HRESULT Graphics::_initDevice()
{
	HRESULT result = CreateDXGIFactory1(IID_PPV_ARGS(&m_pFactory));
	if (FAILED(result))
	{
		printf("【RenderManager】: Failed To Create Factory\n");
		return result;
	}

	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	result = m_pFactory->EnumAdapterByGpuPreference(
		0,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
		IID_PPV_ARGS(&pAdapter)
	);
	if (FAILED(result))
	{
		printf("FAILED To Get Adapter\n");
		return result;
	}


	//Direct3Dデバイスの初期化
	result = D3D12CreateDevice(
		pAdapter.Get(),
		D3D_FEATURE_LEVEL_12_1,
		IID_PPV_ARGS(m_pDevice.GetAddressOf())
	);
	if (FAILED(result))
	{
		printf("FAILED To Get Create Device\n");
		return result;
	}

	return result;
}

// バックバッファーの初期化処理
HRESULT Graphics::_initBackBuffer()
{
	// バックバッファーを宣言
	UINT swapChainBufferCount = m_swapChain.GetDesc().BufferCount;
	m_backBuffers.resize(swapChainBufferCount);

	// レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ガンマ補正のあるフォーマット
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	// バックバッファーの生成
	auto rtvHandle = m_rtvHeap.GetCPUHeapHandle();
	for (size_t i = 0; i < swapChainBufferCount; ++i) {
		HRESULT result = m_swapChain.Get()->GetBuffer(
			static_cast<UINT>(i),
			IID_PPV_ARGS(m_backBuffers[i].GetAddressOf())
		);
		if (FAILED(result))
			return result;

		m_pDevice.Get()->CreateRenderTargetView(
			m_backBuffers[i].Get(),
			&rtvDesc,
			rtvHandle
		);

		UINT allocateSize = m_pDevice.Get()->GetDescriptorHandleIncrementSize(
			D3D12_DESCRIPTOR_HEAP_TYPE_RTV
		);
		rtvHandle.ptr += allocateSize;
	}

	return S_OK;
}

// デバイスを取得する
ID3D12Device* Graphics::GetDevice()
{
	return m_pDevice.Get();
}


// ディスクリプタを取得する
DescriptorHeap& Graphics::GetDescriptorHeap()
{
	return m_mainHeap;
}

ID3D12GraphicsCommandList* Graphics::GetCommandList()
{
	return m_commandList.Get();
}