#pragma once

#include "Framework/Render/Resource/Texture.h"
#include "Shader.h"

#include <string>

class Material
{
public:
	// 初期化処理
	bool Init(std::string _filePath);

	// テクスチャを取得する
	Render::Texture* GetTexture() const;

	// メインテクスチャを設定する
	void SetTexture(Render::Texture* const _pNewTexture);

	// マテリアルのファイルパスを取得する
	std::string GetFilePath() const;

	// シェーダーを取得する
	Shader* GetShader() const;
	
	// 現在のマテリアルデータをファイルに保存する
	void SaveToFile() const;
protected:
	// マテリアル名
	std::string m_filePath;
	// マテリアルに使われるテクスチャ
	Render::Texture* m_pMainTexture;
	// マテリアルに使われるシェーダー
	Shader* m_pShader;
};
