#pragma once

#include <string>
#include <fstream>

// nlohmannライブラリを使うためインクルード
#include "nlohmann/json.hpp"

namespace Assets
{
	class JsonLoader
	{
		// コピーを禁止する
		JsonLoader(const JsonLoader&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const JsonLoader&) = delete;

	public:
		// コンストラクタ
		JsonLoader(){}
		// デストラクター
		~JsonLoader(){}

		/// <summary>
		/// Jsonファイルから構造体のメンバーごとの値を読み込む
		/// </summary>
		/// <typeparam name="T"> 戻り値のデータ型 </typeparam>
		/// <param name="_filePath"> ファイルパス </param>
		/// <returns> ファイルに書いてあるデータ </returns>
		template<typename T>
		T LoadJson(const std::string& _filePath)
		{
			std::ifstream file(_filePath);

			nlohmann::basic_json jsonFile;
			file >> jsonFile;

			return jsonFile.get<T>();
		}
	};
}