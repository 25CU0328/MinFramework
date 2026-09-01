

#include "SelectionManager.h"
#ifdef EDITOR_DEF

// 選択されたゲームオブジェクトを設定する
void SelectionManager::SetSelectedObejct(GameObject* const _pObject)
{
	m_pSelectedObject = _pObject;
}
// 選択されたゲームオブジェクトを取得する
GameObject* SelectionManager::GetSelectedObject() const
{
	return m_pSelectedObject;
}

#endif // EDITOR_DEF