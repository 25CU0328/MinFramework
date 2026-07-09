#pragma once


// 入力関連の処理をするマネージャー
class InputManager
{
	// コピーを禁止する
	InputManager(const InputManager&) = delete;
	// オペレーターによるコピーを禁止する
	void operator = (const InputManager&) = delete;
public:
	// コンストラクタ
	InputManager();
	// デストラクター
	~InputManager();

	// 更新処理
	void Update();

	// キーを長押しするかを判断する
	bool GetKeyPressed(int key);

	// キーを離すかを判断する
	bool GetKeyUp(int _key);

	// キーを押すかを判断する
	bool GetKeyDown(int _key);

private:
	// 今フレームで押されたキーの記録
	bool m_currentKeys[256];
	// 前フレームで押されたキーの記録
	bool m_previousKeys[256];
};