
#include "RenderManager.h"

// ImGuiマネージャーの処理を呼び出すため
#include "Framework/Framework.h"

// コンストラクタ
Render::RenderManager::RenderManager()
	: m_graphics()
	, m_renderers()
{

}
// デストラクター
Render::RenderManager::~RenderManager()
{

}



// 初期化処理
bool Render::RenderManager::Init(HWND* _hwnd)
{
	return m_graphics.Init(_hwnd);
}

void Render::RenderManager::QueueRender(Renderer* _pRenderObject)
{
	if (_pRenderObject == nullptr)
		return;

	m_renderers.emplace_back(_pRenderObject);
}

void Render::RenderManager::Render()
{
	// フレーム開始の処理
	m_graphics.BeginFrame();

	// 
	ID3D12GraphicsCommandList* pCommandList = m_graphics.GetCommandList();
	
	// 使われたシェーダーが同じかどうかを確認するための変数
	Shader* pCurrentShader = nullptr;

	// 描画の優先順位によって整列する
	std::sort(
		m_renderers.begin(),
		m_renderers.end(),
		[](Renderer* pRenderer1, Renderer* pRenderer2) {
			return pRenderer1->GetRenderPriority() < pRenderer2->GetRenderPriority();
		}
	);

	std::vector<RenderData> meshRenderDatas;
	
	for (Renderer* pRenderer : m_renderers)
	{
		pRenderer->GetRenderDatas(meshRenderDatas);

		for (const RenderData& data : meshRenderDatas)
		{
			// 適応されたマテリアルと前回のオブジェクトが
			// 同じシェーダーを使っているかをチェックする
			Shader* pShader = data.pMaterial->GetShader();
			if (pCurrentShader != pShader)
			{
				// ルートシグネチャーを設定する
				pCommandList->SetGraphicsRootSignature(
					pShader->GetRootSignature()
				);

				// パイプラインステートを設定する
				pCommandList->SetPipelineState(
					pShader->GetPipelineState()
				);


				pCurrentShader = pShader;
			}

			Render::Texture* pTexture = data.pMaterial->GetTexture();
			if (pTexture)
			{
				// ディスクリプタテーブルの設定
				pCommandList->SetGraphicsRootDescriptorTable(
					0, // ルートパラメーターインデックス
					pTexture->GetGPUHandle()
				);
			}
			// 定数バッファーを設定する
			pCommandList->SetGraphicsRootConstantBufferView(
				1,
				data.pConstantBuffer->GetResource()->GetGPUVirtualAddress()
			);

			// 行列計算
			{
				// 計算結果
				XMMATRIX matrix = pRenderer->GetWorldMatrix()
					* m_pCamera->GetViewProjectionMatrix();

				// objとDirectXの座標系が異なるための処理
				matrix = XMMatrixTranspose(matrix);
				data.pConstantBuffer->UpdateMatrix(&matrix, sizeof(matrix));
			}


			// バーテックスバッファーを設定する
			pCommandList->IASetVertexBuffers(0, 1, &data.vertexBufferView);
			// インデックスバッファーを設定する
			pCommandList->IASetIndexBuffer(&data.indexBufferView);
			// 
			pCommandList->DrawIndexedInstanced(data.indexNum, 1, 0, 0, 0);
		}
	}
	
	ImGui_I->BeginFrame();

	ImGui_I->Render();

	ImGui_I->EndFrame();

	// フレーム終了の処理
	m_graphics.EndFrame();

	// 記録されたレンダリングオブジェクトをクリア
	m_renderers.clear();
}


Render::Graphics* Render::RenderManager::GetGraphics()
{
	return &m_graphics;
}

// カメラを設定する
void Render::RenderManager::SetCamera(Camera* _pCamera)
{
	m_pCamera = _pCamera;
}