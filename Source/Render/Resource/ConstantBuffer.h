#pragma once

#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Render/ComPtr.h"
#include "DescriptorHeap.h"
#include "DirectXMath.h"

/*
	GPUのシェーダーへ、頻繁に変わるデータを渡すためのバッファ

	座標変換に使う行列やライドの情報など
*/

namespace Render
{
	// 定数バッファーを表すクラス
	class ConstantBuffer
	{
		// コピーを禁止する
		ConstantBuffer(const ConstantBuffer&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const ConstantBuffer&) = delete;

	public:
		// コンストラクタ
		ConstantBuffer();
		// デストラクター
		~ConstantBuffer();

		// 初期化処理
		bool Init(ID3D12Device* _pDevice);
		// 行列データを更新する
		void UpdateMatrix(void* data, UINT size);

		// 定数バッファーの本体を取得する
		ID3D12Resource* GetResource() const;

		// バッファーのGPU位置を取得
		D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const;
	private:
		// 定数バッファーの本体
		ComPtr<ID3D12Resource> m_pResource;

		// 領域マッピング用の変数
		void* m_mappedData = nullptr;
	};
}
