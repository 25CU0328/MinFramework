#pragma once

#include <d3d12.h>

#include <DirectXTex.h>
#pragma comment(lib,"DirectXTex.lib")

#include "Assets/Image/ImageData.h"
#include "Render/ComPtr.h"

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

	private:
		// テクスチャのバッファー
		ComPtr<ID3D12Resource> m_pResource;
	};
}
