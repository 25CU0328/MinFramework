
#include "Material.h"

#include "Framework.h"

// 初期化処理
bool Runtime::Material::Init(std::string _filePath)
{
	Render::Texture* pTexture = Assets_I->LoadTexture(_filePath);

	if (pTexture == nullptr)
	{
		printf("[Material]テクスチャが取得できませんでした\n");
		return false;
	}

	m_pTexture = pTexture;

	return true;
}

// テクスチャを取得する
Render::Texture* Runtime::Material::GetTexture() const
{
	return m_pTexture;
}