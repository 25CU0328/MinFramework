#pragma once

// ImageDataを使用するためインクルード
#include "ImageData.h"

namespace Assets
{
	namespace Image
	{
		class ImageLoader
		{
			// コピーを禁止する
			ImageLoader(const ImageLoader&) = delete;
			// オペレーターによるコピーを禁止する
			void operator = (const ImageLoader&) = delete;

		public:
			// コンストラクタ
			ImageLoader();
			// デストラクター
			~ImageLoader();

			/// <summary>
			/// 画像ファイルを指定のパスから読み込む
			/// </summary>
			/// <param name="_pFilePath"> ファイルパス </param>
			/// <param name="_outData"> データ受け取るための変数 </param>
			/// <returns> 読み込みの結果 </returns>
			bool LoadImageFile(
				const wchar_t* _pFilePath, 
				ImageData& _outData
			);
		};
	}
}