

#include "ShaderObject.h"
using namespace Render;

// シェーダーファイルをコンパイルためにインクルード
#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

ShaderObject::ShaderObject()
{

}

ShaderObject::~ShaderObject()
{

}

// 初期化処理
bool ShaderObject::Init(LPCWSTR _filePath, ShaderType _shaderType)
{
	ID3DBlob* errorBlob = nullptr;

	// シェーダーをコンパイル
	HRESULT result = D3DCompileFromFile(
		_filePath,										// ファイル名
		nullptr,										// シェーダーのマクロオブジェクト
		D3D_COMPILE_STANDARD_FILE_INCLUDE,				// シェーダーに必要なライブラリ設定
		_getEntryString(_shaderType),					// エントリーポイント名
		_getShaderTypeString(_shaderType),				// シェーダーの種類(ps, vsなど)
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,// シェーダーのコンパイルオプション
		0,												// エフェクトコンパイルオプション
		m_pBlob.GetAddressOf(),							// 受け取るための変数
		&errorBlob										// エラーメッセージ
	);

	if (FAILED(result))
	{
		printf("Failed to Create ShaderObject\n");
		return false;
	}

	if (m_pBlob.Get() == nullptr)
	{
		printf("Blob is nullptr");
		return false;
	}

	return true;
}

// 後片付け処理
void ShaderObject::Term()
{
	m_pBlob->Release();
}

// ルートシグネチャーを取得
ID3DBlob* ShaderObject::GetBlob() const
{
	return m_pBlob.Get();
}

// シェーダーエントリーポイントの文字列を取得する
LPCSTR ShaderObject::_getEntryString(ShaderType _shaderType)
{
	switch (_shaderType)
	{
	case ShaderType::VertexShader:
		return "VSMain";
		break;

	case ShaderType::PixelShader:
		return "PSMain";
		break;
	}
}

// シェーダー種類の文字列を取得する
LPCSTR ShaderObject::_getShaderTypeString(ShaderType _shaderType)
{
	// ここは全部5.0にする
	switch (_shaderType)
	{
	case ShaderType::VertexShader:
		return "vs_5_0";
		break;

	case ShaderType::PixelShader:
		return "ps_5_0";
		break;
	}
}

// シェーダーのデータを取得
void* ShaderObject::GetShaderByteCode()
{
	return m_pBlob->GetBufferPointer();
}

// シェーダーデータのサイズを取得
SIZE_T ShaderObject::GetShaderByteCodeLength()
{
	return m_pBlob->GetBufferSize();
}