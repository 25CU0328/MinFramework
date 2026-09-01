#pragma once

#include "EditorDef.h"

#ifdef EDITOR_DEF

#include "Framework/Runtime/GameObject.h"

class SelectionManager
{
public:
	// 選択されたゲームオブジェクトを設定する
	void SetSelectedObejct(GameObject* const _pObject);
	// 選択されたゲームオブジェクトを取得する
	GameObject* GetSelectedObject() const;


private:
	// 選択されたゲームオブジェクト
	GameObject* m_pSelectedObject;
	
	// 選択されたアセット
	// Asset* m_pSelectedAsset;
};

#endif // EDITOR_DEF