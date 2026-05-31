
#include "VertexBuffer.h"
using namespace Render;


// コンストラクタ・デストラクター
VertexBuffer::VertexBuffer()
    : m_pBuffer(nullptr)
    , m_bufferView(D3D12_VERTEX_BUFFER_VIEW())
{

}

VertexBuffer::~VertexBuffer()
{

}

/// <summary>
/// バーテックスバッファーの初期化処理
/// </summary>
/// <param name="_pDevice"> デバイス </param>
/// <param name="_dataSize"> バーテックス配列(確保した領域)のサイズ </param>
/// <param name="_sizePerVertex"> 各バーテックスデータのサイズ </param>
/// <param name="vertexData"> バーテックス配列のアドレス </param>
/// <returns> (bool)初期化処理が完成されたか </returns>
bool VertexBuffer::Init(
    ID3D12Device* _pDevice,     // デバイス
    UINT64 _dataSize,           // バーテックス配列(確保した領域)のサイズ
    UINT _sizePerVertex,        // 各バーテックスデータのサイズ
    void* _pVertexData      // バーテックス配列のアドレス
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
        resourceDesc.Width = _dataSize * _sizePerVertex;
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
        printf("【VertexBuffer】: Faied to Create Resource\n");
        return false;
    }

    // バーテックス情報をGPUに書き込み
    {
        // 複製するための一時ポインター
        void* mappedPtr = nullptr;

        result = m_pBuffer->Map(0, nullptr, &mappedPtr);
        if (FAILED(result))
        {
            return false;
        }
        memcpy(mappedPtr, _pVertexData, _dataSize * _sizePerVertex);

        m_pBuffer->Unmap(0, nullptr);
    }
    // バーテックスバッファービューの設定
    {
        m_bufferView.BufferLocation = 
            m_pBuffer->GetGPUVirtualAddress();      //バッファの仮想アドレス

        m_bufferView.SizeInBytes = _dataSize * _sizePerVertex;       //全バイト数
        m_bufferView.StrideInBytes = _sizePerVertex;//1頂点あたりのバイト数
    }

    return true;
}


D3D12_VERTEX_BUFFER_VIEW& VertexBuffer::GetView()
{
	return m_bufferView;
}
