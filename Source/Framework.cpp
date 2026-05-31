
#include "Framework.h"

Framework* Framework::s_pInstance = nullptr;

// 初期化処理
bool Framework::Init(const HWND* _hwnd)
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

	return true;
}
// 更新処理
void Framework::Update()
{
	
}
// 物理計算を行うための更新処理
void Framework::LateUpdate()
{

}

// 描画開始の処理
void Framework::StartRender()
{
	// レンダリング開始する前の事前準備
	m_renderManager.StartRender();
}

// 描画が終わった時の処理
void Framework::EndRender()
{
	// レンダリング終わった後の処理
	m_renderManager.EndRender();
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