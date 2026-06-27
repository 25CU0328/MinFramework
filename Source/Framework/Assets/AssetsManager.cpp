
#include "AssetsManager.h"
using namespace Assets;

// コンストラクタ
AssetsManager::AssetsManager() 
	: m_imageLoader()
	, m_modelLoader()
	, m_textureMap()
{

}

// デストラクター
AssetsManager::~AssetsManager()
{
	auto iterator = m_textureMap.begin();
	while (iterator != m_textureMap.end())
	{
		delete iterator->second;
		++iterator;
	}

	m_textureMap.clear();
}

// モデルファイルの読み込み
bool AssetsManager::LoadModelFile(std::string _strFileName, ModelData& _outData)
{
	return m_modelLoader.LoadObjModel(_strFileName, _outData);
}

// 画像ファイルの読み込み
bool AssetsManager::LoadImageFile(std::string _strFileName, ImageData& _outData)
{
	std::wstring wstrFileName(_strFileName.begin(), _strFileName.end());

	return m_imageLoader.LoadImageFile(wstrFileName.c_str(), _outData);
}

// テクスチャを読み込み、又はマップから取得する
Render::Texture* AssetsManager::GetTexture(std::string _filePath)
{
	Render::Texture* pTexture = nullptr;
	// 既に読み込んだTextureから、同じファイル名のテクスチャを取得する
	auto iterator = m_textureMap.find(_filePath);

	// 同じファイル名が存在する場合
	if (iterator != m_textureMap.end())
	{
		pTexture = iterator->second;
		return pTexture;
	}
	else
	{
		ImageData imageData = {};
		// ファイルを成功に読み込まれたら
		if (LoadImageFile(_filePath, imageData))
		{
			pTexture = new Render::Texture();
			if (!pTexture->Init(imageData))
			{
				delete pTexture;
				return nullptr;
			}

			m_textureMap.emplace(_filePath, pTexture);
		}
		else
		{
			return nullptr;
		}
	}

	return pTexture;
}

// シェーダーを読み込む、又はマップから取得する
Runtime::Shader* AssetsManager::GetShader(std::string _filePath)
{
	Runtime::Shader* pShader;

	// 既に読み込んだTextureから、同じファイル名のテクスチャを取得する
	auto iterator = m_shaderMap.find(_filePath);

	// 同じファイル名が存在する場合、名前に対応するシェーダーを返す
	if (iterator != m_shaderMap.end())
	{
		pShader = iterator->second;
		return pShader;
	}
	// ファイル名が存在しない場合、ファイルを読み込む
	else
	{
		// ファイルに書いてあるデータを読み込む
		ShaderData shaderData = FromJson<ShaderData>(_filePath);
		
		pShader = new Runtime::Shader();
		// もし初期化が失敗したら
		if (!pShader->Init(shaderData))
		{
			printf("[AssetsManager]：Failed to Initialize Shader\n");
			return nullptr;
		}

		return pShader;
	}
}
