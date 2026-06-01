#pragma once

#include <d3d12.h>
#include <cstdint>

#include <vector>
#include <string>

#include "Render/ComPtr.h"


namespace Render
{
	enum class ShaderType
	{
		VertexShader,
		PixelShader,
	};


	class ShaderObject
	{
		ShaderObject(const ShaderObject&) = delete;
		void operator = (const ShaderObject&) = delete;
	public:
		ShaderObject();
		~ShaderObject();

		// 初期化処理
		bool Init(LPCWSTR _filePath, ShaderType _shaderType);
		// 後片付け処理
		void Term();

		// ルートシグネチャーを取得
		ID3DBlob* GetBlob() const;

		void* GetShaderByteCode();
		SIZE_T GetShaderByteCodeLength();

	private:
		// シェーダーエントリーポイントの文字列を取得する
		LPCSTR _getEntryString(ShaderType _shaderType);
		// シェーダー種類の文字列を取得する
		LPCSTR _getShaderTypeString(ShaderType _shaderType);

	private:
		// シェーダーオブジェクト(Blob)の本体
		ComPtr<ID3DBlob> m_pBlob;
	};

}
