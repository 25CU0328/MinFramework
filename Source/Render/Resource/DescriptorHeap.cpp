
#include "DescriptorHeap.h"
using namespace Render;


// コンストラクタ
DescriptorHeap::DescriptorHeap()
	: m_pDescriptorHeap(nullptr)
	, m_CPU_Handle(D3D12_CPU_DESCRIPTOR_HANDLE())
	, m_GPU_Handle(D3D12_GPU_DESCRIPTOR_HANDLE())
	, m_heapDesc(D3D12_DESCRIPTOR_HEAP_DESC())
{

}

// デストラクタ
DescriptorHeap::~DescriptorHeap()
{
	
}

// 初期化処理
bool DescriptorHeap::Init(
	ID3D12Device* _pDevice,
	D3D12_DESCRIPTOR_HEAP_TYPE _type,
	D3D12_DESCRIPTOR_HEAP_FLAGS _flag,
	UINT _DescirptorNum
)
{
	// デストラクターの設定
	{
		// 種別設定
		m_heapDesc.Type = _type;
		// フラグ設定
		m_heapDesc.Flags = _flag;
		// 
		m_heapDesc.NodeMask = 0;
		// デストラクター数
		m_heapDesc.NumDescriptors = _DescirptorNum;
	}
	
	// デストラクターオブジェクトの生成
	HRESULT result = _pDevice->CreateDescriptorHeap(
		&m_heapDesc,
		IID_PPV_ARGS(m_pDescriptorHeap.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("【DescriptorHeap】：Failed to Create DescirptorHeap\n");
		return false;
	}

	m_CPU_Handle = m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	
	// Noneの場合、GPUのHandleがアクセス不可になります
	if (_flag != D3D12_DESCRIPTOR_HEAP_FLAG_NONE)
	{
		m_GPU_Handle = m_pDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	}

	return true;
}

// 後片付け処理
void DescriptorHeap::Term()
{
	m_pDescriptorHeap->Release();
}

// ヒープ上の新しい要素の位置を取得
D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUHeapHandle() const
{
	return m_CPU_Handle;
}

// ヒープ上の新しい要素の位置を取得
D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGPUHeapHandle() const
{
	return m_GPU_Handle;
}

D3D12_DESCRIPTOR_HEAP_DESC DescriptorHeap::GetDesc() const
{
	return m_heapDesc;
}

// 対応するサイズの領域をアロケート
// (ヒープに要素を追加した場合)
void DescriptorHeap::AllocateCPU(const UINT _allocateSize)
{
	m_CPU_Handle.ptr += _allocateSize;
}

// 対応するサイズの領域をアロケート
// (ヒープに要素を追加した場合)
void DescriptorHeap::AllocateGPU(const UINT _allocateSize)
{
	m_GPU_Handle.ptr += _allocateSize;
}

// ディスクリプタヒープの本体を取得する
ID3D12DescriptorHeap* DescriptorHeap::Get()
{
	return m_pDescriptorHeap.Get();
}
