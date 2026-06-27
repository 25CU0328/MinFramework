#pragma once

#include "Mesh.h"
#include "Framework/Assets/Model/ModelData.h"

namespace Runtime
{
	class Model
	{
	public:

		// 初期化処理
		bool Init(
			ModelData _data, 
			std::string _materialName = ""
		);

		// メッシュを描画する
		void Draw();

	private:
		std::vector<Mesh*> m_pMeshes;
	};
}