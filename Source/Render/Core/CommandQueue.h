#pragma once

#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Render/ComPtr.h"


/*
	CommandListの命令を発送し、
	命令の同期を担当するクラス

	また、Fenceクラスと組み合わせることで、
	CPUとGPUの同期を行う
*/

namespace Render 
{
	class CommandQueue
	{
		// オブジェクトの複製を禁止する
		CommandQueue(const CommandQueue&) = delete;
		// オペレーターによるコピーを禁止する
		CommandQueue operator = (const CommandQueue&) = delete;

	public:
		// コンストラクタ・デストラクター
		CommandQueue();
		~CommandQueue();

		// 初期化処理
		bool Init(ID3D12Device* _pDevice);

		// 後片付け処理
		void Term();

		// コマンドリストを取得するためのメソッド
		ID3D12CommandQueue* Get();

		/// <summary>
		/// コマンドリストの命令を実行する
		/// </summary>
		/// <param name="_listNum"> コマンドリストの数 </param>
		/// 
		/// <param name="_ppCommandLists"> 
		/// 渡されたコマンドリストのポインター配列
		/// </param>
		void Execute(UINT _listNum, ID3D12CommandList** _ppCommandLists);

	private:
		// コマンドキューの本体
		ComPtr<ID3D12CommandQueue> m_pCommandQueue;
	};
}
