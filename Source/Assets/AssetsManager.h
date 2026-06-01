#pragma once

#include "Model/ModleLoader.h"
#include "Image/ImageLoader.h"

namespace Assets
{
	class AssetsManager
	{
		// コピーを禁止する
		AssetsManager(const AssetsManager&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const AssetsManager&) = delete;

	public:
		// コンストラクタ
		AssetsManager();
		// デストラクター
		~AssetsManager();

		/// <summary>
		/// モデルファイルの読み込み
		/// </summary>
		/// <param name="_strFileName"> ファイル名 </param>
		/// <param name="_outData"> データを受け取るための変数 </param>
		/// <returns> モデルデータ </returns>
		bool LoadModelFile(std::string _strFileName, ModelData& _outData);

		/// <summary>
		/// 画像ファイルの読み込み
		/// </summary>
		/// <param name="_fileName"> ファイル名 </param>
		/// <param name="_outData"> データを受け取るための変数 </param>
		/// <returns> 読み込みは成功したか </returns>
		bool LoadImageFile(const wchar_t* _fileName, ImageData& _outData);

	private:
		Image::ImageLoader m_imageLoader;
		Model::ModleLoader m_modelLoader;
	};
}