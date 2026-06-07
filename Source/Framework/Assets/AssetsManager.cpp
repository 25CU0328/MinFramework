
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
Render::Texture* AssetsManager::LoadTexture(std::string _filePath)
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