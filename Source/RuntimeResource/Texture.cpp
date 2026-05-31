
#include "Texture.h"

// マネージャーを取得するためにインクルード
#include "Framework.h"

// テクスチャの初期化処理
bool Runtime::Texture::Init(const wchar_t* _pFilePath)
{
	// 画像の読み込み
	if (!Assets_I->LoadImageFile(_pFilePath, m_data))
	{
		printf("[Texture]：Failed To load File\n");
		return false;
	}

	// テクスチャバッファーの初期化
	if (!m_buffer.Init(
		Render_I->GetDevice(),
		m_data,
		Render_I->GetDescriptorHeap()
	))
	{
		printf("[Texture]：Failed To Init Texture Buffer\n");
		return false;
	}


	return true;
}

// 画像データの取得
ImageData Runtime::Texture::GetData() const
{
	return m_data;
}