#pragma once
#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Render/ComPtr.h"

#include <DirectXTex.h>
#pragma comment(lib,"DirectXTex.lib")

#include "Render/Resource/DescriptorHeap.h"
#include "Assets/Image/ImageData.h"

namespace Render
{
	class TextureBuffer
	{
		// オブジェクトの複製を禁止する
		TextureBuffer(const TextureBuffer&) = delete;
		// オペレーターによるコピーを禁止する
		TextureBuffer operator = (const TextureBuffer&) = delete;

	public:
		// コンストラクタ
		TextureBuffer();
		// デストラクター
		~TextureBuffer();

		// 初期化処理
		bool Init(
			ID3D12Device* _pDevice,
			const ImageData _imageData,
			DescriptorHeap& _pDescriptorHeap
		);

		// 後片付け処理
		void Term();

		// テクスチャのリソースを返す関数
		ID3D12Resource* GetResource() const;


	private:
		ComPtr<ID3D12Resource> m_pResource;
	};
}
