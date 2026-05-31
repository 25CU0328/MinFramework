
#include "Fence.h"
using namespace Render;

// コンストラクタ・デストラクター
Fence::Fence()
{
	m_pFence = nullptr;
	m_fenceValue = 0;

    m_event = CreateEvent(nullptr, false, false, nullptr);
}

Fence::~Fence()
{
    Term();
}

// 初期化処理
bool Fence::Init(
	ID3D12Device* _pDevice
)
{
	HRESULT result = _pDevice->CreateFence(
		m_fenceValue,
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(m_pFence.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("【Fence】Failed to Create Fence\n");
		return false;
	}

    // イベントを生成.
    m_event = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);

	return true;
}

// 後片付け処理
void Fence::Term()
{
    m_pFence.Reset();

    CloseHandle(m_event);
}

// コマンドリストを取得するためのメソッド
ID3D12Fence* Fence::Get()
{
	return m_pFence.Get();
}

// GPUに命令を渡す
// GPUの処理が終わるまで、又は時間切れまで待機する
void Fence::SynAndWait(ID3D12CommandQueue* _pCommandQueue, UINT _waitTime)
{
    if (_pCommandQueue == nullptr)
        return;

    const auto fenceValue = m_fenceValue;

    HRESULT result = _pCommandQueue->Signal(m_pFence.Get(), fenceValue);

    if (FAILED(result))
        return;

    // カウンターを増やす.
    m_fenceValue++;

    // 次のフレームの描画準備がまだであれば待機する.
    if (m_pFence->GetCompletedValue() < fenceValue)
    {
        // 完了時にイベントを設定.
        auto hr = m_pFence->SetEventOnCompletion(fenceValue, m_event);
        if (FAILED(hr))
            return;

        // 待機処理.
        if (WAIT_OBJECT_0 != WaitForSingleObjectEx(m_event, _waitTime, FALSE))
        {
            return;
        }
    }
}