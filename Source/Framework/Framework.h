#pragma once

#include "Render/RenderManager.h"
#include "Assets/AssetsManager.h"
#include "TimeManager.h"
#include "Input/InputManager.h"
#include "Collision/CollisionManager.h"
#include "ImGui/ImGuiManager.h"

#include "App.h"

// マネージャーを取得するためのマクロ
#define Framework_I Framework::GetInstance()
#define Render_I Framework_I->GetRenderManager()
#define Assets_I Framework_I->GetAssetsManager()
#define Time_I Framework_I->GetTimeManager()
#define Input_I Framework_I->GetInputManager()
#define Collision_I Framework_I->GetCollisionManager()
#define ImGui_I Framework_I->GetImGuiManager()

/*
	フレームワークの重要機能を管理するためのクラス

	また、それらの更新を行います
*/
class Framework
{
	static Framework* s_pInstance;

public:
	// 初期化処理
	bool Init(HWND* _pHWND);
	// 更新処理
	void Update();
	// 物理計算を行うための更新処理
	void LateUpdate();

	// 描画処理
	void Render();

	// 描画開始の処理
	void StartRender();
	// 描画が終わった後の処理
	void EndRender();

	// フレームワークシャットダウンの後片付け
	void Term();

	// フレームワークの実体(ポインター)を取得
	static Framework* GetInstance();
	// アセットマネージャーを取得する
	Assets::AssetsManager* GetAssetsManager();
	// レンダーマネージャーを取得する
	Render::RenderManager* GetRenderManager();

	// 時間のマネージャーを取得する
	TimeManager* GetTimeManager();

	// 入力関連処理のマネージャーを取得する
	InputManager* GetInputManager();

	// 衝突判定のマネージャーを取得する
	CollisionManager* GetCollisionManager();

	// ImGuiマネージャーを取得する
	ImGuiManager* GetImGuiManager();
private:
	// 描画関連処理のマネージャー
	Render::RenderManager m_renderManager;
	// アセットのマネージャー
	Assets::AssetsManager m_assetsManager;

	// 時間マネージャー
	TimeManager m_timeManager;

	// 入力マネージャー
	InputManager m_inputManager;

	// 衝突判定のマネージャー
	CollisionManager m_collisionManager;
	
	// ImGui関連処理のマネージャー
	ImGuiManager m_ImGuiManager;
};
