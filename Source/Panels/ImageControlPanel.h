#pragma once

#include "Framework/ImGui/ImGuiPanel.h"

#include "ImageControlPanel.h"
#include "Framework/Runtime/Sprite.h"

class ImageControlPanel : public ImGuiPanel
{
public:
	// 初期化処理
	void Init(const char* _panelName = "", Runtime::Sprite* _targetSprite = nullptr);

	// 描画処理
	void Render();

private:
	// スプライトの位置
	Vector2f m_spritePosition;
	// スプライトのサイズ
	Vector2f m_spriteSize;
	// 回転
	int m_spriteRotation;

	// コントロール対象となるスプライト
	Runtime::Sprite* m_pSprite;
};