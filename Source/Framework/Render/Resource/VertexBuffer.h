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
			ID3D12Device* _pDevice,     // デバイス
			UINT64 _dataSize,           // バーテックス配列(確保した領域)のサイズ
			UINT _sizePerVertex,        // 各バーテックスデータのサイズ
			void* _pVertexData      // バーテックス配列のアドレス
		);

		// バーテックスバッファーの記述子を取得する
		D3D12_VERTEX_BUFFER_VIEW& GetView();
	private:
		// バーテックスバッファーの本体
		ComPtr<ID3D12Resource> m_pBuffer;
		// バーテックスバッファーの記述子
		D3D12_VERTEX_BUFFER_VIEW m_bufferView;
	};
}
