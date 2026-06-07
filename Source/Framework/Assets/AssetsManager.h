#pragma once

#include <unordered_map>
#include <fstream>


#include "Model/ModleLoader.h"
#include "Image/ImageLoader.h"
#include "Json/JsonLoader.h"

#include "Framework/Render/Resource/Texture.h"

// nlohmannライブラリを使うためインクルード
#include "nlohmann/json.hpp"


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
		bool LoadImageFile(std::string _filePath, ImageData& _outData);

		/// <summary>
		/// テクスチャを取得する
		/// </summary>
		/// <param name="_filePath"></param>
		/// <returns></returns>
		Render::Texture* LoadTexture(std::string _filePath);

		/// <summary>
		/// Jsonファイルから構造体のデータを読み込む
		/// </summary>
		/// <typeparam name="T"> 指定されたデータ型 </typeparam>
		/// <param name="_strFileName"> ファイルパス </param>
		/// <returns> 構造体のデータ </returns>
		template<typename T>
		T FromJson(std::string _filePath)
		{
			return m_jsonLoader.LoadJson<T>(_filePath);
		}

	private:
		Image::ImageLoader m_imageLoader;
		Model::ModleLoader m_modelLoader;
		JsonLoader m_jsonLoader;
		// テクスチャデータを管理するマップ
		std::unordered_map<std::string, Render::Texture*> m_textureMap;
	};
}