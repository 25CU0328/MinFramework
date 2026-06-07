
#include "DepthStencilBuffer.h"
using namespace Render::Resource;

#include "AppDef.h"
// コンストラクタ
DepthStencilBuffer::DepthStencilBuffer()
	: m_dsBuffer()
	, m_dsvHeap()
	, m_viewDesc()
{

}

// デストラクター
DepthStencilBuffer::~DepthStencilBuffer()
{

}

// 初期化処理
bool DepthStencilBuffer::Init(
	ID3D12Device* _pDevice
)
{
	if (!m_dsvHeap.Init(
		_pDevice,
		D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
		D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
		1
	))
	{
		return false;
	}

	// バッファー本体(ID3D12Resource)の設定
	D3D12_RESOURCE_DESC resourceDesc = {};
	{
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

		resourceDesc.Width = WINDOW_WIDTH;
		resourceDesc.Height = WINDOW_HEIGHT;

		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;

		resourceDesc.Format = DXGI_FORMAT_D32_FLOAT;

		resourceDesc.SampleDesc.Count = 1;

		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	}

	// デフォルトのヒープを使用
	D3D12_HEAP_PROPERTIES heapProp = {};
	{
		heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	}

	// クリア設定
	D3D12_CLEAR_VALUE clearValue = {};
	{
		clearValue.Format = DXGI_FORMAT_D32_FLOAT;

		clearValue.DepthStencil.Depth = 1.0f;
		clearValue.DepthStencil.Stencil = 0;
	}

	HRESULT result =_pDevice->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(m_dsBuffer.GetAddressOf())
	);

	if (FAILED(result))
		return false;
	
	// デプスステンシルの設定
	{
		// データのフォーマット
		m_viewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		// データの次元(1D, 2Dなど)
		m_viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	}

	_pDevice->CreateDepthStencilView(
		m_dsBuffer.Get(),
		&m_viewDesc,
		m_dsvHeap.GetCPUHeapHandle()
	);

	return true;
}

// 領域の位置を取得する
D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilBuffer::GetHandle() const
{
	return m_dsvHeap.GetCPUHeapHandle();
}

// デプスステンシルバッファーの本体を取得する
ID3D12Resource* DepthStencilBuffer::GetResource() const
{
	return m_dsBuffer.Get();
}

// バッファーの設定を取得
D3D12_RESOURCE_DESC DepthStencilBuffer::GetDesc() const
{
	return m_dsBuffer->GetDesc();
}

// デプスステンシルの設定を取得する
D3D12_DEPTH_STENCIL_VIEW_DESC DepthStencilBuffer::GetViewDesc() const
{
	return m_viewDesc;
}