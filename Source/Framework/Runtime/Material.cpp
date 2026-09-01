
#include "Material.h"

#include "Framework/Framework.h"
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

	// ファイルパスを保存する
	m_filePath = _filePath;

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
	// 引数がヌルの場合、処理しない
	if (!_pNewTexture)
		return;

	m_pMainTexture = _pNewTexture;
}

// マテリアル名を取得する
std::string Material::GetFilePath() const
{
	return m_filePath;
}

// シェーダーを取得する
Shader* Material::GetShader() const
{
	return m_pShader;
}

// 現在のマテリアルデータをファイルに保存する
void Material::SaveToFile() const
{
	MaterialData data;
	{
		data.textureName = m_pMainTexture->GetFilePath();
		data.shaderName = m_pShader->GetFilePath();
	}

	// ファイルに書き込む
	Assets_I->WriteJsonFile(m_filePath, data);
}