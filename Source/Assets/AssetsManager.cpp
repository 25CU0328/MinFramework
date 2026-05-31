
#include "AssetsManager.h"
using namespace Assets;

// コンストラクタ
AssetsManager::AssetsManager() :
	m_imageLoader(),
	m_modelLoader()
{

}

// デストラクター
AssetsManager::~AssetsManager()
{

}

// モデルファイルの読み込み
bool AssetsManager::LoadModelFile(std::string _strFileName, ModelData& _outData)
{
	return m_modelLoader.LoadObjModel(_strFileName, _outData);
}

// 画像ファイルの読み込み
bool AssetsManager::LoadImageFile(const wchar_t* _fileName, ImageData& _outData)
{
	return m_imageLoader.LoadImageFile(_fileName, _outData);
}