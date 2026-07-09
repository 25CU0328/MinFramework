
#include "InputManager.h"

#include <windows.h>
#include <iostream>

// コンストラクタ
InputManager::InputManager()
    : m_currentKeys()
    , m_previousKeys()
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
}

// キーを長押しするかを判断する
bool InputManager::GetKeyPressed(int _key)
{
    return m_previousKeys[_key] && m_currentKeys[_key];
}

// キーを離すかを判断する
bool InputManager::GetKeyUp(int _key)
{
    return m_previousKeys[_key] && !m_currentKeys[_key];
}

// キーを押すかを判断する
bool InputManager::GetKeyDown(int _key)
{
    return !m_previousKeys[_key] && m_currentKeys[_key];
}