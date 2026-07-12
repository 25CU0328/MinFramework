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

		// 描画の優先順位を設定する
		void SetRenderPriority(const int _priority);
		// 描画の優先順位を取得する
		int GetRenderPriority() const;

	private:
		std::vector<Mesh*> m_pMeshes;

		int m_renderPriority;	// 描画の優先順位
	};
}