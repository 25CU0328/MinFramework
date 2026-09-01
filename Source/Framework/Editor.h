#pragma once

#include "Editor/EditorDef.h"

#ifdef EDITOR_DEF

#include "Editor/SceneInspector.h"
#include "Editor/SelectionManager.h"


// エディター関連機能を管理するクラス
class Editor
{
public:



private:
	SelectionManager* m_pSelectionManager;
};

#endif // EDITOR_DEF