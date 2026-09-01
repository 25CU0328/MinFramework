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
		JsonLoader() {}
		// デストラクター
		~JsonLoader() {}

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

			nlohmann::basic_json jsonData;
			file >> jsonData;

			return jsonData.get<T>();
		}

		/// <summary>
		/// データをJSONファイルを上書き・保存する
		/// </summary>
		/// <typeparam name="T"> 上書き・保存したいデータのデータ型 </typeparam>
		/// <param name="_filePath"> 上書き・保存したいファイルパス </param>
		/// <param name="_newData"> 上書き・保存したいデータ </param>
		template<typename T>
		void WriteToJson(const std::string& _filePath, const T& _data)
		{
			// 構造体メンバーをJsonDataに代入
			nlohmann::basic_json jsonData;
			jsonData = _data;

			// 出力ファイルを開く
			std::ofstream file(_filePath);

			// ファイルを上書き・保存する
			file << jsonData.dump(4);
		}
	};
}