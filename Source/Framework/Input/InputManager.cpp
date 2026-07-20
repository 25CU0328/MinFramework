
#include "InputManager.h"

#include <windows.h>
#include <iostream>

#include "Framework/Framework.h"

// コンストラクタ
InputManager::InputManager()
    : m_currentKeys()
    , m_previousKeys()
    , m_currentMousePosition()
    , m_previousMousePosition()
    , m_originalCursorPosition()
    , m_isCursorVisible(true)
    , m_isResetCursor(true)
{
    
}
// デストラクター
InputManager::~InputManager()
{

}

// 更新処理
void InputManager::Update()
{
    // 今回結果を前回結果の配列にコピーする
    memcpy(m_previousKeys, m_currentKeys, sizeof(m_currentKeys));

    // 今フレームでキーが押したかどうかの判断結果を記録する
    for (int i = 0; i < 256; i++)
    {
        m_currentKeys[i] = (GetAsyncKeyState(i) & 0x8000);
    }

    // 現在のマウス位置をコピーする
    m_previousMousePosition = m_currentMousePosition;

    // カーソル位置を取得するための一時的変数
    POINT tempPoint;
    // カーソル位置を取得する
    GetCursorPos(&tempPoint);
    // ウィンドウ上に対応する位置を取得する
    ScreenToClient(
        *Render_I->GetGraphics()->GetHWND(), 
        &tempPoint
    );

    // 取得した位置を記録する
    m_currentMousePosition = Vector2f(tempPoint.x, tempPoint.y);
}

// キーを長押しするかを判断する
bool InputManager::IsKeyPressed(const KeyCode _key) const
{
    return m_previousKeys[static_cast<int>(_key)] 
        &&  m_currentKeys[static_cast<int>(_key)];
}

// キーを離すかを判断する
bool InputManager::IsKeyUp(const KeyCode _key) const
{
    return m_previousKeys[static_cast<int>(_key)] 
        && !m_currentKeys[static_cast<int>(_key)];
}

// キーを押すかを判断する
bool InputManager::IsKeyDown(const KeyCode _key) const
{
    return !m_previousKeys[static_cast<int>(_key)] 
        &&   m_currentKeys[static_cast<int>(_key)];
}



// マウスが長押しされたかを判断する
bool InputManager::IsMousePressed(const MouseButton _targetButton) const
{
    return m_previousKeys[static_cast<int>(_targetButton)]
        && m_currentKeys[static_cast<int>(_targetButton)];
}

// マウスが離されたかを判断する
bool InputManager::IsMouseUp(const MouseButton _targetButton) const
{
    return m_previousKeys[static_cast<int>(_targetButton)]
        && !m_currentKeys[static_cast<int>(_targetButton)];
}

// マウスが押されたかを判断する
bool InputManager::IsMouseDown(const MouseButton _targetButton) const
{
    return !m_previousKeys[static_cast<int>(_targetButton)]
        &&   m_currentKeys[static_cast<int>(_targetButton)];
}

// マウス位置を取得する
Vector2f InputManager::GetMousePosition() const
{
    return Vector2f(
        m_currentMousePosition.x, 
        m_currentMousePosition.y
    );
}

// 前回マウス位置との差を取得する
Vector2f InputManager::GetMousePositionDelta() const
{
    return Vector2f(
        m_currentMousePosition.x - m_previousMousePosition.x,
        m_currentMousePosition.y - m_previousMousePosition.y
    );
}

// カーソルを表示・非表示する
void InputManager::SetCursorVisible(const bool _isVisible)
{
    if (!(_isVisible ^ m_isCursorVisible))
        return;

    m_isCursorVisible = _isVisible;

    if (_isVisible)
    {
        SetCursorPos(
            m_originalCursorPosition.x,
            m_originalCursorPosition.y
        );
        // カーソルを表示する
        ShowCursor(true);
    }
    else
    {
        // カーソル位置を取得する
        GetCursorPos(&m_originalCursorPosition);
        // カーソルを非表示にする
        ShowCursor(false);
    }
}

// カーソルの位置をリセット毎フレーム
void InputManager::SetResetCursorPerFrame(const bool _isReset)
{
    // 設定したい状態と今の状態が同じ場合、処理しない
    if (!(m_isResetCursor ^ _isReset))
        return;

    m_isResetCursor = _isReset;

    // リセットにする時、元の位置を記録する
    if (_isReset)
    {
        GetCursorPos(&m_originalCursorPosition);
    }
}