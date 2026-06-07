#pragma once

#include <unordered_map>

#include "Model/ModleLoader.h"
#include "Image/ImageLoader.h"

#include "Render/Resource/Texture.h"

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
		bool LoadImageFile(std::string _strFileName, ImageData& _outData);

		/// <summary>
		/// テクスチャを取得する
		/// </summary>
		/// <param name="_filePath"></param>
		/// <returns></returns>
		Render::Texture* LoadTexture(std::string _filePath);

	private:
		Image::ImageLoader m_imageLoader;
		Model::ModleLoader m_modelLoader;

		// テクスチャデータを管理するマップ
		std::unordered_map<std::string, Render::Texture*> m_textureMap;
	};
}