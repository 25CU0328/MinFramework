#pragma once

#include <iostream>

#include "Assets/Image/ImageData.h"
#include "Render/Resource/TextureBuffer.h"

namespace Runtime
{
	class Texture
	{
	public:

		/// <summary>
		/// テクスチャの初期化処理
		/// </summary>
		/// <param name="_pFilePath"></param>
		/// <returns> テクスチャの読み込み結果 </returns>
		bool Init(const wchar_t* _pFilePath);

		/// <summary>
		/// 画像データの取得
		/// </summary>
		/// <returns> 画像データ </returns>
		ImageData GetData() const;

	private:
		ImageData m_data;
		Render::TextureBuffer m_buffer;
	};
}