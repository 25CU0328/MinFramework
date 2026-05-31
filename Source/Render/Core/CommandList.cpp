

#include "CommandList.h"
using namespace Render;
// コンストラクタ
CommandList::CommandList()
	: m_pCommandList(nullptr)
	, m_pAllocators()
{

}
// デストラクター
CommandList::~CommandList()
{
	Term();
}

// コマンドリストの初期化
bool CommandList::Init(
	ID3D12Device* _pDevice,
	D3D12_COMMAND_LIST_TYPE _commandType,
	uint32_t _bufferCount
)
{
	if (_pDevice == NULL || _bufferCount <= 0)
	{
		return false;
	}

	// バッファー数ごとのアロケーターを作成
	{
		m_pAllocators.resize(_bufferCount);

		for (int i = 0; i < _bufferCount; ++i)
		{
			// D3D装置上にアロケーターを作成
			auto result = _pDevice->CreateCommandAllocator(
				_commandType,
				IID_PPV_ARGS(m_pAllocators[i].GetAddressOf())
			);

			// アロケーターの作成が失敗したらfalseと返す
			if (FAILED(result))
			{
				printf("Failed to Create Allocator");
				return false;
			}
		}
	}

	{
		// D3D装置上にコマンドリストを作成
		auto result = _pDevice->CreateCommandList(
			1,
			_commandType,
			m_pAllocators[0].Get(),
			NULL,
			IID_PPV_ARGS(m_pCommandList.GetAddressOf())
		);

		// コマンドリストの作成が失敗したらfalseと返す
		if (FAILED(result))
		{
			printf("Failed to Create CommandList");
			return false;
		}

		m_pCommandList->Close();
	}

	return true;
}

// 後片付け
void CommandList::Term()
{
	// ここのリセットはComPtrのリセットであり
	// コマンドリストのリセットではありません

	m_pCommandList.Reset();

	for (size_t i = 0; i < m_pAllocators.size(); ++i)
	{
		m_pAllocators[i].Reset();
	}

	m_pAllocators.clear();
}

// コマンドリストのリセット
void CommandList::Reset(uint32_t _index)
{
	if (_index > m_pAllocators.size())
	{
		printf("【CommandList】: Try to Reset with index more than allocator\n");
		return;
	}


	// アロケーターをリセット
	auto result = m_pAllocators[_index]->Reset();

	if (FAILED(result))
		return;

	result = m_pCommandList->Reset(m_pAllocators[_index].Get(), nullptr);

	if (FAILED(result))
		return;


}

// コマンドリスト本体を取得する
ID3D12GraphicsCommandList* CommandList::Get() const
{
	return m_pCommandList.Get();
}