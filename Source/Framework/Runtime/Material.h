#pragma once

#include "Render/Resource/Texture.h"
#include "string"
namespace Runtime
{
	class Material
	{
	public:
		// 初期化処理
		bool Init(std::string _filePath);

		// テクスチャを取得する
		Render::Texture* GetTexture() const;


	private:
		Render::Texture* m_pTexture;
	};
}