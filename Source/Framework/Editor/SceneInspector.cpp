
#include "SceneInspector.h"
#ifdef EDITOR_DEF

#include "Framework/Framework.h"
// 初期化処理
void SceneInspector::Init(const char* _panelName, const Vector2f _minimunSize)
{
    ImGuiPanel::Init(_panelName, _minimunSize);
}

// 描画処理
void SceneInspector::Render()
{
    ImGuiPanel::Render();

    ImGui::Begin(m_panelName);

    m_pScene = Scene_I->GetCurrentScene();

    // 現在シーンが存在する場合
    if (m_pScene)
    {
        // シーンにある全てのオブジェクトを取得する
        std::vector<GameObject*> sceneObjects = m_pScene->GetGameObjets();

        for (auto pObject : sceneObjects)
        {
            // ルートオブジェクトの場合、描画処理を行う
            if (!pObject->GetComponent<Transform>()->GetParent())
            {
                _drawNode(pObject);
            }
        }
    }

    ImGui::End();
}

// ゲームオブジェクトを表示する
void SceneInspector::_drawNode(GameObject* _pObject)
{
    Transform* pTransform = _pObject->GetComponent<Transform>();

    bool opened =ImGui::TreeNode((void*)_pObject, _pObject->GetName().c_str());

    if (ImGui::IsItemClicked())
    {
        m_pSelectedObject = _pObject;
    }

    if (opened)
    {
        for (auto pChild : pTransform->GetChildren())
        {
            _drawNode(pChild->GetGameObject());
        }

        ImGui::TreePop();
    }
}

// ドラッグ&ドロップ処理
void SceneInspector::_dragDrop()
{
    if (ImGui::BeginDragDropSource())
    {
        GameObject* pObject = m_pDragObject;

        ImGui::SetDragDropPayload(
            "GAMEOBJECT",
            &pObject,
            sizeof(GameObject*)
        );

        ImGui::Text("%s",
            pObject->GetName().c_str());

        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload =
            ImGui::AcceptDragDropPayload("GAMEOBJECT"))
        {
            GameObject* pDragged =
                *(GameObject**)payload->Data;

            pDragged->GetComponent<Transform>()
                ->SetParent(
                    m_pDragObject
                    ->GetComponent<Transform>());
        }

        ImGui::EndDragDropTarget();
    }
}
#endif