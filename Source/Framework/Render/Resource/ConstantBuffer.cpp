
#include "ConstantBuffer.h"
using namespace Render;

#include "Framework/Render/d3dx12.h"

#include "AppDef.h"
using namespace DirectX;

ConstantBuffer::ConstantBuffer():
	m_pResource()
{

}

ConstantBuffer::~ConstantBuffer()
{

}

// 初期化処理
bool ConstantBuffer::Init(ID3D12Device* _pDevice)
{
	// ヒーププロパティ
	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソースディスクリプタ
	auto ResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(256);

	HRESULT result = _pDevice->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_pResource.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("FAILED To Create Commited Resource\n");
		return false;
	}

	result = m_pResource->Map(0, nullptr, &m_mappedData);
	if (FAILED(result))
	{
		printf("[ConstantBuffer]: Failed TO Map data\n");
		return false;
	}

	return true;
}

// データの更新
void ConstantBuffer::UpdateMatrix(void* data, UINT size) const
{
	memcpy(m_mappedData,data,size);
}

// 定数バッファーの本体を取得する
ID3D12Resource* ConstantBuffer::GetResource() const
{
	return m_pResource.Get();
}

// バッファーのGPU位置を取得
D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGPUAddress() const
{
	return m_pResource->GetGPUVirtualAddress();
}
