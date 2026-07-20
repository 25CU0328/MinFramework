#pragma once

#include "KeyCode.h"
#include "MouseButton.h"

#include "Framework/Math/Vector2.h"

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

	// キーを長押しされたかを判断する
	bool IsKeyPressed(const KeyCode _key) const;
	// キーが離されたかを判断する
	bool IsKeyUp(const KeyCode _key) const;
	// キーを押されたかを判断する
	bool IsKeyDown(const KeyCode _key) const;

	// マウスが長押しされたかを判断する
	bool IsMousePressed(const MouseButton _targetButton) const;
	// マウスが離されたかを判断する
	bool IsMouseUp(const MouseButton _targetButton) const;
	// マウスが押されたかを判断する
	bool IsMouseDown(const MouseButton _targetButton) const;
	// マウス位置を取得する
	Vector2f GetMousePosition() const;
	// 前回マウス位置との差を取得する
	Vector2f GetMousePositionDelta() const;

	// カーソルを表示・非表示する
	void SetCursorVisible(const bool _isVisible);
	// カーソルの位置をリセット毎フレーム
	void SetResetCursorPerFrame(const bool _isReset);

private:
	// 今フレームで押されたキーの記録
	bool m_currentKeys[256];
	// 前フレームで押されたキーの記録
	bool m_previousKeys[256];
	
	// 今フレームのマウス位置
	Vector2f m_currentMousePosition;
	// 前フレームのマウス位置
	Vector2f m_previousMousePosition;

	// カーソルをリセットするため
	// 位置を記録する変数
	POINT m_originalCursorPosition;

	// カーソルが表示されているか
	bool m_isCursorVisible;

	// カーソルの移動をロックするか
	bool m_isResetCursor;
};