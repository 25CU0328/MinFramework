

#include "CommandQueue.h"
using namespace Render;




// コンストラクタ
CommandQueue::CommandQueue()
{

}
// デストラクター
CommandQueue::~CommandQueue()
{

}

// 初期化処理
bool CommandQueue::Init(ID3D12Device* _pDevice)
{
	// コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	// コマンドキューの生成
	HRESULT result = _pDevice->CreateCommandQueue(
		&desc,
		IID_PPV_ARGS(m_pCommandQueue.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("Failed to Create CommandQueue\n");
		return false;
	}

	return true;
}

// 後片付け処理
void CommandQueue::Term()
{
	m_pCommandQueue->Release();
}

// コマンドリストを取得するためのメソッド
ID3D12CommandQueue* CommandQueue::Get()
{
	return m_pCommandQueue.Get();
}

// コマンドリストの命令を実行する
void CommandQueue::Execute(UINT _listNum, ID3D12CommandList** _ppCommandLists)
{
	m_pCommandQueue->ExecuteCommandLists(_listNum, _ppCommandLists);
}