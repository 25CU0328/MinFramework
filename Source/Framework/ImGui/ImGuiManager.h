
#pragma once

#include "Framework/Render/Resource/DescriptorHeap.h"

class ImGuiManager
{
public:
	// 初期化処理
	void Init();

	// フレーム開始時の処理
	void BeginFrame();

	// 更新処理
	void Render();

	// フレーム終了時の処理
	void EndFrame();

	void Term();


private:
	Render::DescriptorHeap m_descriptorHeap;
};