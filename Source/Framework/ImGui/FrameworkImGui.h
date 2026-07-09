
#pragma once

#include "Framework/Render/Resource/DescriptorHeap.h"

class FrameworkImGui
{

public:
	// 初期化処理
	void Init();

	// 更新処理
	void CreateUIs();

	// 描画処理
	void Render();

	void Term();


private:
	Render::DescriptorHeap m_descriptorHeap;
};