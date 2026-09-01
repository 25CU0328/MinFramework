#pragma once

#include "Framework/Runtime/Mesh.h"
#include "Framework/Render/Resource/Texture.h"
#include "Framework/Assets/Model/ModelData.h"
#include "Renderer.h"

#include <string>

class MeshRenderer : public Renderer
{
public:
	MeshRenderer() { m_componentType = GameComponentType::MeshRenderer; }
	~MeshRenderer(){}
public:
	// メッシュを描画する
	void Render();

	// 描画するメッシュを設定する
	void SetMesh(const ModelData& _data);

	// マテリアルを設定する
	void SetMaterial(std::string _materialPath);

	// テクスチャを設定する
	void SetTexture(std::string _texturePath);

	// 描画用データを取得する
	void GetRenderDatas(std::vector<RenderData>& _outRenderDatas) const;

	// コンポネントデータを取得する
	GameComponentData GetComponentData() const;

	// コンポネントを設定する
	void SetComponent(const GameComponentData _componentData);

private:
	// モデルファイルのファイルパス
	std::string m_filePath;

	// モデルにある全てのメッシュ
	std::vector<Mesh*> m_pMeshes;

	// マテリアル
	Material m_material;

	// 描画の優先順位
	int m_renderPriority;	
};
