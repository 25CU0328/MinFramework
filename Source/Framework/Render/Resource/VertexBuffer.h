#pragma once
#include <d3d12.h>
#include <cstdint>
#include <vector>
#include<dxgi1_6.h>

#include "Framework/Render/ComPtr.h"

/*
	メッシュのバーテックス情報を持つバッファー
*/


namespace Render
{
	class VertexBuffer
	{
		// オブジェクトの複製を禁止する
		VertexBuffer(const VertexBuffer&) = delete;
		// オペレーターによるコピーを禁止する
		VertexBuffer operator = (const VertexBuffer&) = delete;

	public:
		// コンストラクタ・
		VertexBuffer();
		// デストラクター
		~VertexBuffer();

		/// <summary>
		/// バーテックスバッファーの初期化処理
		/// </summary>
		/// <param name="_pDevice"> デバイス </param>
		/// <param name="_dataSize"> バーテックス配列(確保した領域)のサイズ </param>
		/// <param name="_sizePerVertex"> 各バーテックスデータのサイズ </param>
		/// <param name="vertexData"> バーテックス配列のアドレス </param>
		/// <returns> (bool)初期化処理が完成されたか </returns>
		bool Init(
			ID3D12Device* _pDevice,     
			UINT64 _dataSize,           
			UINT _sizePerVertex,        
			void* _pVertexData
		);

		/// <summary>
		/// バーテックスデータを更新する
		/// </summary>
		/// <param name="_pVertexData"> 新しいデータのアドレス </param>
		/// <param name="_dataSize"> バーテックス配列のサイズ </param>
		/// <param name="_sizePerVertex"> 各バーテックスデータのサイズ </param>
		void UpdateVertex(void* _pVertexData, UINT64 _dataSize, UINT _sizePerVertex);

		// バーテックスバッファーの記述子を取得する
		D3D12_VERTEX_BUFFER_VIEW& GetView();

	private:
		// バーテックスバッファーの本体
		ComPtr<ID3D12Resource> m_pBuffer;
		// バーテックスバッファーの記述子
		D3D12_VERTEX_BUFFER_VIEW m_bufferView;
	};
}
