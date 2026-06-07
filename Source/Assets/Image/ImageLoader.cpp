

#include "ImageLoader.h"

// コンストラクタ
Assets::Image::ImageLoader::ImageLoader()
{

}
// デストラクター
Assets::Image::ImageLoader::~ImageLoader()
{

}

// 画像ファイルを指定のパスから読み込む
bool Assets::Image::ImageLoader::LoadImageFile(
	const wchar_t* _pFilePath,
	ImageData& _outData
)
{
	// ファイルの読み込み(DirectXTex使用)
	HRESULT result = LoadFromWICFile(
		_pFilePath,
		DirectX::WIC_FLAGS_NONE,
		&_outData.metaData,
		_outData.scratchImage
	);

	if (FAILED(result))
	{
		printf("【ImageLoader】Failed to Load Image\n");
		return false;
	}

	return true;
}