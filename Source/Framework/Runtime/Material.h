#pragma once

#include "Framework/Render/Resource/Texture.h"
#include "Shader.h"

#include <string>
namespace Runtime
{
	class Material
	{
	public:
		// 初期化処理
		bool Init(std::string _filePath);

		// テクスチャを取得する
		Render::Texture* GetTexture() const;

		// メインテクスチャを設定する
		void SetTexture(Render::Texture* const _pNewTexture);

		// シェーダーを取得する
		Shader* GetShader() const;
		
	protected:
		Render::Texture* m_pMainTexture;
		Shader* m_pShader;
	};
}