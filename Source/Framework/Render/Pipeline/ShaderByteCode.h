#pragma once

#include <d3d12.h>
#include <cstdint>

#include <vector>
#include <string>

#include "Render/ComPtr.h"

/*
	シェーダーファイル (.hlsl)をコンパイルで転換した
	バイトコード
	
*/


namespace Render
{
	enum class ShaderType
	{
		VertexShader,
		PixelShader,
	};


	class ShaderByteCode
	{
		ShaderByteCode(const ShaderByteCode&) = delete;
		void operator = (const ShaderByteCode&) = delete;
	public:
		ShaderByteCode();
		~ShaderByteCode();

		// 初期化処理
		bool Init(LPCWSTR _filePath, ShaderType _shaderType);
		// 後片付け処理
		void Term();

		// ルートシグネチャーを取得
		ID3DBlob* GetBlob() const;

		// シェーダーバイトコードのバッファーを取得する
		void* GetBuffer();
		// バイトコードのサイズを取得する
		SIZE_T GetSize();

	private:
		// シェーダーエントリーポイントの文字列を取得する
		LPCSTR _getEntryString(ShaderType _shaderType);
		// シェーダー種類の文字列を取得する
		LPCSTR _getShaderTypeString(ShaderType _shaderType);

	private:
		// シェーダーバイトコード(Blob)の本体
		ComPtr<ID3DBlob> m_pBlob;
	};
}
