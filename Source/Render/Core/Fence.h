#pragma once

#include <d3d12.h>
#include <cstdint>
#include <vector>

#include "Render/ComPtr.h"

/*
	CPUとGPUの同期を担当するオブジェクト
*/


namespace Render
{
	class Fence
	{
		// オブジェクトの複製を禁止する
		Fence(const Fence&) = delete;
		// オペレーターによるコピーを禁止する
		Fence operator = (const Fence&) = delete;

	public:
		// コンストラクタ・デストラクター
		Fence();
		~Fence();

		// 初期化処理
		bool Init(ID3D12Device* _pDevice);

		// 後片付け処理
		void Term();

		// コマンドリストを取得するためのメソッド
		ID3D12Fence* Get();

		/// <summary>
		/// GPUに命令を渡す
		/// GPUの処理が終わる、又は時間切れまで待機する
		/// </summary>
		/// <param name="_pCommandQueue"> 渡す命令を持つCommandQueue </param>
		/// <param name="_waitTime"> 待ち時間 </param>
		void SynAndWait(ID3D12CommandQueue* _pCommandQueue, UINT _waitTime);

	private:
		// フェンス本体
		ComPtr<ID3D12Fence> m_pFence;
		// 同期用のカウンター
		UINT				m_fenceValue;
		// GPUの処理が完了したのコールバック関数
		HANDLE m_event;
	};
}

