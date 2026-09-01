#pragma once

#include "Framework/Runtime/GameObject.h"
#include "Framework/Assets/AssetData/SceneData.h"
class Scene
{
	// コンストラクタ、デストラクター
public:
	Scene();
	~Scene();

public:
	// シーンの初期化
	virtual void Init(SceneData _sceneData);
	// シーンの更新処理
	virtual void Update();
	// シーンの描画処理
	virtual void Render();
	// シーンの終了処理
	virtual void Term();

public:
	// シーンのファイルパスを設定する
	void SetSceneFilePath(const std::string& _filePath);
	// シーンのファイルパスを取得する
	std::string GetSceneFilePath() const;

	// シーン名を設定する
	void SetSceneName(const std::string& _sceneName);
	// シーン名を取得する
	std::string GetSceneName() const;

	// ゲームオブジェクトを追加する
    void AddGameObject(GameObject* const _pNewObject);

	// ゲームオブジェクトを削除する
    void DestroyGameObject(GameObject* const _pObject);

	// ゲームオブジェクトをシーム内番号で取得する
    GameObject* GetGameObjectByIndex(const int _num);

	// ゲームのオブジェクトをIDで取得する
	GameObject* GetGameObjectById(const int _id);

	// ゲームオブジェクトを名前で取得する
    GameObject* GetGameObjectByName(const std::string& _name);

	// シーンデータを取得する
	SceneData GetSceneData() const;

	// シーンにある全てのゲームオブジェクトを取得する
	std::vector<GameObject*>& GetGameObjets();

private:
	// シーンのファイルパス
	std::string m_sceneFilePath;

	// シーン名
	std::string m_sceneName;

    std::vector<GameObject*> m_gameObjects;
};