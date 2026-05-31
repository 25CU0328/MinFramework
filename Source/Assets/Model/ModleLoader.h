#pragma once
// 受け取るためのクラス
#include <assimp/scene.h>	
#include <assimp/Importer.hpp>  // 読み込むためのインポーター
#include <assimp/postprocess.h> // 読み込む時のフラグ設定

#include <iostream>
#include <vector>

#include "ModelData.h"

namespace Assets
{
	namespace Model
	{
		class ModleLoader
		{
			// コピーを禁止する
			ModleLoader(const ModleLoader&) = delete;
			// オペレーターによるコピーを禁止する
			void operator = (const ModleLoader&) = delete;

		public:
			// コンストラクタ
			ModleLoader();
			// デストラクター
			~ModleLoader();

			/// <summary>
			/// 3Dモデルを読み込む
			/// </summary>
			/// <param name="_strFileName"> モデルのファイル名 </param>
			/// <param name="_outData"> データ受け取るための変数 </param>
			/// <returns> モデルの読み込みは成功したかどうか </returns>
			bool LoadObjModel(const std::string _strFileName, ModelData& _outData);

		private:
			// Assimpのシーンデータからメッシュデータを取得
			ModelData _parseSceneData(const aiScene* _pScene);
		};
	}
}