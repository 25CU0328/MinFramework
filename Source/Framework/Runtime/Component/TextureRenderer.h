#pragma once

#include <DirectXMath.h>

#include "Framework/Assets/Image/ImageData.h"
#include "Framework/Runtime/Mesh.h"
#include "Renderer.h"

class TextureRenderer : public Renderer
{
public:
	// コンストラクタ
	TextureRenderer();
	// デストラクター
	~TextureRenderer();

public:
	// 初期化する
	void Init();
	// 描画する
	void Render();
	// テクスチャを設定する
	void SetTexture(Render::Texture* const _pNewTexture);

	// レンダリング用のデータを取得する
	void GetRenderDatas(std::vector<RenderData>& _outRenderDatas) const;

	// コンポネントデータを取得する
	GameComponentData GetComponentData() const;

	// コンポネントを設定する
	void SetComponent(const GameComponentData _componentData);

private:
	// 画像を表示するためのクアッド
	Mesh m_quadMesh;
	// テクスチャ
	Render::Texture* m_pTexture;
	// マテリアル
	Material m_material;
};
