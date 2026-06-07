
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
bool Render::RenderManager::Init(const HWND* _hwnd)
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
	for (Runtime::RenderObject* pObject : m_RenderObjects)
	{
		RenderData data = pObject->GetData();

		// 定数バッファーを設定する
		pCommandList->SetGraphicsRootConstantBufferView(
			1,
			data.pConstantBuffer->GetResource()->GetGPUVirtualAddress()
		);

		// 既にテクスチャデータを取得した場合
		if (data.pMaterial->GetTexture() != nullptr)
		{
			pCommandList->SetGraphicsRootDescriptorTable(
				0,
				m_graphics.GetDescriptorHeap().GetGPUHeapHandle()
			);

			UINT allocateSize = m_graphics.GetDevice()
				->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			m_graphics.GetDescriptorHeap().AllocateCPU(allocateSize);
		}
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