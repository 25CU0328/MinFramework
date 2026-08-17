
#include "Material.h"

#include "Framework/Framework.h"
#include "Framework/Assets/AssetData/MaterialData.h"
#include "Framework/Assets/AssetData/MaterialData.h"

// 初期化処理
bool Material::Init(std::string _filePath)
{
	MaterialData materialData = Assets_I->FromJson<MaterialData>(_filePath);

	if (materialData.shaderName == "")
	{
		printf("[Material]：Shader didn't set properly\n");
		return false;
	}

	// アセットマネージャーからシェーダーを取得する
	m_pShader = Assets_I->GetShader(materialData.shaderName);

	// テクスチャを設定する
	if (materialData.textureName == "")
	{
		m_pMainTexture = Assets_I->GetTexture("Assets/Image/Default.png");
	}
	else
	{
		m_pMainTexture = Assets_I->GetTexture(materialData.textureName);
	}

	return true;
}

// テクスチャを取得する
Render::Texture* Material::GetTexture() const
{
	return m_pMainTexture;
}

// メインテクスチャを設定する
void Material::SetTexture(Render::Texture* const _pNewTexture)
{
	m_pMainTexture = _pNewTexture;
}

// シェーダーを取得する
Shader* Material::GetShader() const
{
	return m_pShader;
}