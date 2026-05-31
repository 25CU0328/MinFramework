#pragma once

#include "Render/RenderManager.h"
#include "Assets/AssetsManager.h"

#include "App.h"

// マネージャーを取得するためのマクロ
#define Framework_I Framework::GetInstance()
#define Render_I Framework_I->GetRenderManager()
#define Assets_I Framework_I->GetAssetsManager()

/*
	フレームワークの重要機能を管理するためのクラス
	
	また、それらの更新を行います
*/
class Framework
{
	static Framework* s_pInstance;

public:
	// 初期化処理
	bool Init(const HWND* _pHWND);
	// 更新処理
	void Update();
	// 物理計算を行うための更新処理
	void LateUpdate();

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
private:

	Render::RenderManager m_renderManager;
	Assets::AssetsManager m_assetsManager;

};
