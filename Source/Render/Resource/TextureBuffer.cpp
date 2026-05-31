
#include "TextureBuffer.h"
using namespace Render;


// コンストラクタ
TextureBuffer::TextureBuffer()
{

}
// デストラクター
TextureBuffer::~TextureBuffer()
{

}

// 初期化処理
bool TextureBuffer::Init(
	ID3D12Device* _pDevice,
	const ImageData _imageData,
	DescriptorHeap& _descriptorHeap
)
{
	// -----------------
	// テクスチャ設定
	// -----------------
	D3D12_HEAP_PROPERTIES texHeapProp = {};
	{
		// 特殊な設定なので、
		texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
		texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		// 転送はL0、つまりCPU側から直接行う
		texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		// 単一アダプターのため、0にする
		texHeapProp.CreationNodeMask = 0;
		texHeapProp.VisibleNodeMask = 0;
	}

	// リソースの設定
	D3D12_RESOURCE_DESC texResDesc = {};
	{
		texResDesc.Format = _imageData.metaData.format;
		// サイズ指定
		texResDesc.Width = _imageData.metaData.width;
		texResDesc.Height = _imageData.metaData.height;
		// 2D配列ではないので 1にする
		texResDesc.DepthOrArraySize = 1;
		texResDesc.SampleDesc.Count = 1;
		texResDesc.SampleDesc.Quality = 0;

		// ミップマップしないのでミップ数は1
		texResDesc.MipLevels = 1;
		// 2Dテクスチャー用
		texResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		// レイアウトを決定しない
		texResDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		// 特にフラグなし
		texResDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	}

	// テクスチャのバッファー
	HRESULT result = _pDevice->CreateCommittedResource(
		&texHeapProp,
		// 特に指定なし
		D3D12_HEAP_FLAG_NONE,
		&texResDesc,
		// テクスチャ用指定
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(m_pResource.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("【TextureResouce】：Failed to Create Texture Buffer\n");
		return false;
	}

	result = m_pResource->WriteToSubresource(
		0,
		nullptr,
		_imageData.image->pixels,		// 元データアドレス
		_imageData.image->rowPitch,	// 1ラインサイズ
		_imageData.image->slicePitch	// 1枚サイズ
	);

	if (FAILED(result))
	{
		printf("【TextureResouce】：Failed to Write to Subresource\n");
		return false;
	}

	// ディスクリプタの設定情報
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	{
		// RBGA (0.0f~1.0に正規化)
		srvDesc.Format = _imageData.metaData.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		// 2Dテクスチャ
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		// ミップマップは使用しないので1
		srvDesc.Texture2D.MipLevels = 1;
	}


	// ディスクリプタの生成
	_pDevice->CreateShaderResourceView(
		// ビューと関連付けるバッファー
		m_pResource.Get(),
		// 先ほど設定したテクスチャ設定情報
		&srvDesc,
		// 先頭アドレス
		_descriptorHeap.GetCPUHeapHandle()
	);

	// ディスクリプタの位置を移動する
	UINT offset = _pDevice->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
	);
	_descriptorHeap.AllocateCPU(offset);

	return true;
}

// 後片付け処理
void TextureBuffer::Term()
{

}

// テクスチャバッファーの本体を取得する
ID3D12Resource* TextureBuffer::GetResource() const
{
	return m_pResource.Get();
}
