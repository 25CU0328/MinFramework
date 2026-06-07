#pragma once

#include "Graphics.h"

#include "Framework/Render/RenderData.h"
#include "Framework/Runtime/RenderObject.h"
#include "Framework/Runtime/Camera.h"
/*
	フレーム使用者としての描画責任者

	DirectXに関するレンダリング命令や
	オブジェクトの管理はGraphicsManagerが担当する
*/


namespace Render
{
	class RenderManager
	{
		// コピーを禁止する
		RenderManager(const RenderManager&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const RenderManager&) = delete;
	public:
		// コンストラクタ
		RenderManager();
		// デストラクター
		~RenderManager();

		Graphics* GetGraphics();

		// 初期化処理
		bool Init(const HWND* _hwnd);

		void QueueRender(Runtime::RenderObject* _pRenderObject);

		// 描画処理
		void Render();

		// カメラを設定する
		void SetCamera(Runtime::Camera* _pCamera);

	private:
		Graphics m_graphics;
		Runtime::Camera* m_pCamera;
		std::vector<Runtime::RenderObject*> m_RenderObjects;
	};
}