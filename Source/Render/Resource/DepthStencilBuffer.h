#pragma once

#include <d3d12.h>

#include "Render/ComPtr.h"
#include "DescriptorHeap.h"
namespace Render
{
	namespace Resource
	{
		class DepthStencilBuffer
		{
			// コピーを禁止する
			DepthStencilBuffer(const DepthStencilBuffer&) = delete;
			// オペレーターによるコピーを禁止する
			void operator = (const DepthStencilBuffer&) = delete;

		public:
			// 初期化処理
			bool Init(
				ID3D12Device* _pDevice
			);
			// コンストラクタ
			DepthStencilBuffer();
			// デストラクター
			~DepthStencilBuffer();

			// 領域の位置を取得
			D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() const;
			// デプスステンシルバッファーの本体
			ID3D12Resource* GetResource() const;
			// バッファーの設定を取得
			D3D12_RESOURCE_DESC GetDesc() const;
			// デプスステンシルの設定を取得
			D3D12_DEPTH_STENCIL_VIEW_DESC GetViewDesc() const;

		private:
			// デプスステンシルバッファーの本体
			ComPtr<ID3D12Resource> m_dsBuffer;
			// 
			DescriptorHeap	m_dsvHeap;
			// デプスステンシルの設定
			D3D12_DEPTH_STENCIL_VIEW_DESC m_viewDesc;
		};
	}
}