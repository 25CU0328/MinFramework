
#include "RenderManager.h"

// コンストラクタ
Render::RenderManager::RenderManager()
	: m_graphics()
	, m_RenderObjects()
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

void Render::RenderManager::QueueRender(Runtime::RenderObject* _pRenderObject)
{
	if (_pRenderObject == nullptr)
		return;

	m_RenderObjects.emplace_back(_pRenderObject);
}

void Render::RenderManager::Render()
{
	// フレーム開始の処理
	m_graphics.BeginFrame();

	// 
	ID3D12GraphicsCommandList* pCommandList = m_graphics.GetCommandList();
	
	// 使われたシェーダーが同じかどうかを確認するための変数
	Runtime::Shader* pCurrentShader = nullptr;
	for (Runtime::RenderObject* pObject : m_RenderObjects)
	{
		RenderData data = pObject->GetData();

		// 適応されたマテリアルと前回のオブジェクトが
		// 同じシェーダーを使っているかをチェックする
		Runtime::Shader* pShader = data.pMaterial->GetShader();
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
			XMMATRIX matrix = pObject->GetWorldMatrix() 
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

	// フレーム終了の処理
	m_graphics.EndFrame();

	// 記録されたレンダリングオブジェクトをクリア
	m_RenderObjects.clear();
}


Render::Graphics* Render::RenderManager::GetGraphics()
{
	return &m_graphics;
}

// カメラを設定する
void Render::RenderManager::SetCamera(Runtime::Camera* _pCamera)
{
	m_pCamera = _pCamera;
}