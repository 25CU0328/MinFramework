
#pragma once

#include "Framework/Render/Resource/DescriptorHeap.h"
#include "ImGuiPanel.h"

#include <vector>

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

	// パネルを登録する
	void RegistPanel(ImGuiPanel* _newPanel);
	// パネルの登録を解除する
	void UnregistPanel(ImGuiPanel* _newPanel);
private:
	Render::DescriptorHeap m_descriptorHeap;

	// ImGuiパネルを管理するベクトル
	std::vector<ImGuiPanel*> m_panels;


};