#pragma once
#include <d3d12.h>
#include <cstdint>
#include <vector>
#include<dxgi1_6.h>

#include "Render/ComPtr.h"

/*
	メッシュのインデックス情報を持つバッファー
*/

namespace Render
{
	class IndexBuffer
	{
		// オブジェクトの複製を禁止する
		IndexBuffer(const IndexBuffer&) = delete;
		// オペレーターによるコピーを禁止する
		IndexBuffer operator = (const IndexBuffer&) = delete;

	public:
		// コンストラクタ・
		IndexBuffer();
		// デストラクター
		~IndexBuffer();

		/// <summary>
		/// インデックスバッファーの初期化処理
		/// </summary>
		/// <param name="_pDevice"> デバイス </param>
		/// <param name="_dataSize"> インデックス配列(確保した領域)のサイズ </param>
		/// <param name="_sizePerVertex"> 各インデックスデータのサイズ </param>
		/// <param name="vertexData"> インデックス配列のアドレス </param>
		/// <returns> (bool)初期化処理が完成されたか </returns>
		bool Init(
			ID3D12Device* _pDevice,	// デバイス
			UINT _datasSize,				// インデックス配列(確保した領域)のサイズ
			UINT _sizePerIndex,				// 各インデックスデータのサイズ
			void* _pIndexDatas		// インデックス配列のアドレス
		);

		/// <summary>
		/// インデックスビューを取得する
		/// </summary>
		/// <returns> インデックスビュー </returns>
		D3D12_INDEX_BUFFER_VIEW& GetView();

	private:
		// インデックスバッファーの本体
		ComPtr<ID3D12Resource> m_pBuffer;
		// インデックスバッファーの記述子
		D3D12_INDEX_BUFFER_VIEW m_bufferView;
	};
}
