
#include "SceneManager.h"

#include "Framework/Framework.h"
// コンストラクタ
SceneManager::SceneManager()
{

}
// デストラクター
SceneManager::~SceneManager()
{

}


// 初期化処理
void SceneManager::Init()
{

}

// シーンをロードする
void SceneManager::LoadScene(const std::string _sceneDataPath)
{
	// 既に読み込んだことあるかを確認する
	auto iterator = std::find_if(
		m_sceneDatas.begin(), 
		m_sceneDatas.end(), 
		[this, _sceneDataPath](const SceneData& sceneData)
		{
			return sceneData.sceneName == _sceneDataPath;
		}
	);

	if (m_currentScene)
	{
		m_currentScene->Term();
		

		delete m_currentScene;
		m_currentScene = nullptr;
	}

	// シーンを読み込んだことある場合
	if (iterator != m_sceneDatas.end())
	{
		// 探したデータを使う
		m_currentScene = new Scene();

		m_currentScene->Init(*iterator);
	}
	// 読み込んだことない場合
	else
	{
		// アセットマネージャーからデータを取得する
		SceneData data = Assets_I->FromJson<SceneData>(_sceneDataPath);

		// ベクターに保存する
		m_sceneDatas.emplace_back(data);

		m_currentScene = new Scene();
		m_currentScene->Init(data);
	}
}

// 現在シーンを取得する
Scene* SceneManager::GetCurrentScene()
{
	return m_currentScene;
}

// 現在シーンをシーンデータに保存・上書きする
void SceneManager::SaveCurrentScene() const
{
	Assets_I->WriteJsonFile(m_currentScene->GetSceneFilePath().c_str(), m_currentScene->GetSceneData());
}