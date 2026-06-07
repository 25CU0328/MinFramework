#pragma once

#include "Mesh.h"
#include "Assets/Model/ModelData.h"

namespace Runtime
{
	class Model
	{
	public:

		// 初期化処理
		bool Init(ModelData _data);

		// メッシュを描画する
		void Draw(Camera* _pCamera);

	private:
		std::vector<Mesh*> m_pMeshes;
	};
}