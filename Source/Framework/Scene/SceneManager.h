#pragma once

#include "Framework/Assets/AssetData/SceneData.h"
#include "Scene.h"

class SceneManager
{
	// コピーを禁止する
	SceneManager(const SceneManager&) = delete;
	// オペレーターによるコピーを禁止する
	void operator = (const SceneManager&) = delete;

public:
	// コンストラクタ
	SceneManager();
	// デストラクター
	~SceneManager();

public:
	// 初期化処理
	void Init();

	// シーンをロードする
	void LoadScene(const std::string _sceneName);

	// 現在シーンを取得する
	Scene* GetCurrentScene();

	// 現在シーンをシーンデータに保存・上書きする
	void SaveCurrentScene() const;

private:
	// 現在シーン
	Scene* m_currentScene;
	// シーンデータを管理するベクター
	std::vector<SceneData> m_sceneDatas;
};
