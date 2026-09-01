
#include "IndexBuffer.h"
using namespace Render;

// コンストラクタ・デストラクター
IndexBuffer::IndexBuffer()
    : m_bufferView()
{

}

IndexBuffer::~IndexBuffer()
{

}

/// <summary>
/// インデックスバッファーの初期化処理
/// </summary>
/// <param name="_pDevice"> デバイス </param>
/// <param name="_dataSize"> インデックス配列(確保した領域)のサイズ </param>
/// <param name="_sizePerVertex"> 各インデックスデータのサイズ </param>
/// <param name="vertexData"> インデックス配列のアドレス </param>
/// <returns> (bool)初期化処理が完成されたか </returns>
bool IndexBuffer::Init(
	ID3D12Device* _pDevice,	// デバイス
	UINT _datasSize,				// インデックス配列(確保した領域)のサイズ
	UINT _sizePerIndex,				// 各インデックスデータのサイズ
	void* _pIndexDatas		// インデックス配列のアドレス
)
{
    // ヒープの設定
    D3D12_HEAP_PROPERTIES heapProperties = {};
    {
        heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
        heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    }

    // リソース(バーテックスバッファー)の設定
    D3D12_RESOURCE_DESC resourceDesc = {};
    {
        resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resourceDesc.Alignment = 0;
        resourceDesc.Width = _datasSize * _sizePerIndex;
        resourceDesc.Height = 1;
        resourceDesc.DepthOrArraySize = 1;
        resourceDesc.MipLevels = 1;
        resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
        resourceDesc.SampleDesc.Count = 1;
        resourceDesc.SampleDesc.Quality = 0;
        resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    }

    // リソース(バーテックスバッファー)の生成
    HRESULT result = _pDevice->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pBuffer)
    );

    if (FAILED(result))
    {
        printf("【IndexBuffer】: Faied to Create Resource\n");
        return false;
    }

    // バーテックスデータをコピー
    {
        void* pMapPointer;

        result = m_pBuffer->Map(0, nullptr, &pMapPointer);
        if (FAILED(result))
        {
            return false;
        }
        memcpy(pMapPointer, _pIndexDatas, _datasSize * _sizePerIndex);

        m_pBuffer->Unmap(0, nullptr);
    }
    // バーテックスバッファービューの設定
    {
        m_bufferView.BufferLocation =
            m_pBuffer->GetGPUVirtualAddress();      //バッファの仮想アドレス

        m_bufferView.SizeInBytes = _datasSize * _sizePerIndex;      //全バイト数
        m_bufferView.Format= DXGI_FORMAT_R32_UINT;  //1頂点あたりのバイト数
    }

    return true;
}


/// <summary>
/// インデックスビューを取得するための関数
/// </summary>
/// <returns> インデックスビュー </returns>
const D3D12_INDEX_BUFFER_VIEW& IndexBuffer::GetView() const 
{
	return m_bufferView;
}