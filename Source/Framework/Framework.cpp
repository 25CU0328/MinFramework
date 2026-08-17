
#include "Framework.h"

Framework* Framework::s_pInstance = nullptr;

// 初期化処理
bool Framework::Init(HWND* _hwnd)
{
	// WICファイルを使うための初期化処理
	HRESULT result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(result))
	{
		printf("[Framework]: CoInitializeEx Failed\n");
		return false;
	}

	if (!m_renderManager.Init(_hwnd))
	{
		printf("[Framework]: RenderManager Init Failed\n");
		return false;
	}

	m_timeManager.Init();

	// ImGuiマネージャーの初期化
	m_ImGuiManager.Init();

	return true;
}
// 更新処理
void Framework::Update()
{
	// 時間マネージャーの更新処理
	m_timeManager.Update();

	// 入力マネージャーの更新処理
	m_inputManager.Update();
}
// 物理計算を行うための更新処理
void Framework::LateUpdate()
{
	m_collisionManager.Update();
}

// 描画処理
void Framework::Render()
{
	// レンダリングマネージャーの描画処理
	m_renderManager.Render();
}

// 描画開始の処理
void Framework::StartRender()
{
	// レンダリング開始する前の事前準備
	m_renderManager.GetGraphics()->BeginFrame();
}

// 描画が終わった時の処理
void Framework::EndRender()
{
	// レンダリング終わった後の処理
	m_renderManager.GetGraphics()->EndFrame();
}

// フレームワークシャットダウンの後片付け
void Framework::Term()
{

}

// フレームワークの実体(ポインター)を取得
Framework* Framework::GetInstance()
{
	if (s_pInstance != nullptr)
		return s_pInstance;

	s_pInstance = new Framework();

	return s_pInstance;
}

// アセットマネージャーを取得する
Assets::AssetsManager* Framework::GetAssetsManager()
{
	return &m_assetsManager;
}
// レンダーマネージャーを取得する
Render::RenderManager* Framework::GetRenderManager()
{
	return &m_renderManager;
}

// 時間のマネージャーを取得する
TimeManager* Framework::GetTimeManager()
{
	return &m_timeManager;
}

// 入力関連処理のマネージャーを取得する
InputManager* Framework::GetInputManager()
{
	return &m_inputManager;
}

// 衝突判定のマネージャーを取得する
CollisionManager* Framework::GetCollisionManager()
{
	return &m_collisionManager;
}

// ImGuiマネージャーを取得する
ImGuiManager* Framework::GetImGuiManager()
{
	return &m_ImGuiManager;
}

// シーンマネージャーを取得する
SceneManager* Framework::GetSceneManager()
{
	return &m_sceneManager;
}