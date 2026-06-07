#pragma once

#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Framework/Render/ComPtr.h"


/*
	コマンドリストとそのアロケーターを管理するクラス
	
	但し、命令の発送はCommandQueueが担当します
*/
namespace Render
{
	class CommandList
	{
		// コピーを禁止する
		CommandList(const CommandList&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const CommandList&) = delete;

	public:
		// コンストラクタ
		CommandList();
		// デストラクター
		~CommandList();

		// 初期化処理
		bool Init(
			ID3D12Device* pDevice,
			D3D12_COMMAND_LIST_TYPE type,
			uint32_t bufferCount
		);
		

		// 後片付け処理
		void Term();

		// コマンドリストのリセット
		void Reset(uint32_t index);

		// コマンドリスト本体を取得する
		ID3D12GraphicsCommandList* Get() const;

	private:
		// コマンドリストの本体
		ComPtr<ID3D12GraphicsCommandList> m_pCommandList;

		// コマンドリストとアロケーターは基本的にセットで使われるため
		// 同じクラスでまとめて管理する

		// コマンドアロケーターを保存するためのプロパティ
		std::vector<ComPtr<ID3D12CommandAllocator>> m_pAllocators;;
	};
}
