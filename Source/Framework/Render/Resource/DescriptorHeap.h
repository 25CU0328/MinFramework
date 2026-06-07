#pragma once

#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Render/ComPtr.h"

/*
	ディスクリプタをまとめたヒープ
	
*/

namespace Render
{
	class DescriptorHeap
	{
		DescriptorHeap(const DescriptorHeap&) = delete;
		void operator = (const DescriptorHeap&) = delete;

	public:
		// コンストラクタ
		DescriptorHeap();
		// デストラクター
		~DescriptorHeap();

		// 初期化処理
		bool Init(
			ID3D12Device* _pDevice,
			D3D12_DESCRIPTOR_HEAP_TYPE _type,
			D3D12_DESCRIPTOR_HEAP_FLAGS _flag,
			UINT _DescirptorNum
		);
		// 後片付け処理
		void Term();

		// CPUハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHeapHandle() const;
		// GPUの
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHeapHandle() const;

		// ディスクリプタヒープの設定情報を取得
		D3D12_DESCRIPTOR_HEAP_DESC GetDesc() const;
		// CPUハンドルに領域
		void AllocateCPU(const UINT allocateSize);
		// ヒープに要素を追加した場合、対応するサイズの領域をアロケート
		void AllocateGPU(const UINT allocateSize);
		// ディスクリプタヒープの本体を取得する
		ID3D12DescriptorHeap* Get();

	private:
		// ディスクリプタヒープの本体
		ComPtr<ID3D12DescriptorHeap> m_pDescriptorHeap;
		// CPU側のハンドル
		D3D12_CPU_DESCRIPTOR_HANDLE m_CPU_Handle;
		// GPU側のハンドル
		D3D12_GPU_DESCRIPTOR_HANDLE m_GPU_Handle;

		// ディスクリプタヒープの設定
		D3D12_DESCRIPTOR_HEAP_DESC m_heapDesc;
	};
}
