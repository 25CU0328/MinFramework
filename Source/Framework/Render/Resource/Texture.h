#pragma once

#include <d3d12.h>

#include <DirectXTex.h>
#pragma comment(lib,"DirectXTex.lib")

#include "Framework/Assets/Image/ImageData.h"
#include "Framework/Render/ComPtr.h"

namespace Render
{
	class Texture
	{
		// オブジェクトの複製を禁止する
		Texture(const Texture&) = delete;
		// オペレーターによるコピーを禁止する
		Texture operator = (const Texture&) = delete;

	public:
		// コンストラクタ
		Texture();
		// デストラクター
		~Texture();

		// 初期化処理
		bool Init(const ImageData& _imageData);

		// 後片付け処理
		void Term();

		// テクスチャのリソースを返す関数
		ID3D12Resource* GetResource() const;

		// バッファーのCPUハンドルを取得する
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle();
		// バッファーのGPUハンドルを取得する
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle();
	private:
		// テクスチャのバッファー
		ComPtr<ID3D12Resource> m_pResource;

		D3D12_CPU_DESCRIPTOR_HANDLE m_CpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE m_GpuHandle;
	};
}
