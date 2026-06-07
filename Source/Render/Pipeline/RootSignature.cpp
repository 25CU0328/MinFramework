
#include "RootSignature.h"
using namespace Render;

#include "Framework.h"

#include <vector>
RootSignature::RootSignature()
{

}

RootSignature::~RootSignature()
{

}

// 初期化処理
bool RootSignature::Init(UINT _samplerNum)
{
	// ------------------------
	// ディスクリプタのレンジ
	// ------------------------

	D3D12_DESCRIPTOR_RANGE descriptorRanges[2] = {};
	// 一番目のレンジ (Shader Resource View)
	// シェーダーをアクセスためのデータ(テクスチャ)
	{
		// テクスチャ数(普通は1)
		descriptorRanges[0].NumDescriptors = 1;
		// レンジの種類
		descriptorRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		// 開始スロットの設定 (基本は0から)
		descriptorRanges[0].BaseShaderRegister = 0;
		// オフセットのサイズ
		descriptorRanges[0].OffsetInDescriptorsFromTableStart =
			D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	}
	// 二番目のレンジ (Constant Buffer View)
	// 転換用の行列・ライト情報などの小型データ
	{
		// テクスチャ数(普通は1)
		descriptorRanges[1].NumDescriptors = 1;
		// レンジの種類
		descriptorRanges[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		// 開始スロットの設定 (基本は1から)
		descriptorRanges[1].BaseShaderRegister = 0;
		// オフセットのサイズ
		descriptorRanges[1].OffsetInDescriptorsFromTableStart =
			D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	}

	// ------------------
	// ルートパラメーター(使い道)
	// ------------------

	// [0] SRV, 
	D3D12_ROOT_PARAMETER rootParameters[2] = {};
	{
		// デストラクターテーブル用
		rootParameters[0].ParameterType =
			D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		// ピクセルシェーダーから見える
		rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		// レンジを設定
		rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRanges[0];
		// デストラクターテーブル数の設定
		rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;
	}
	// [1] CBV
	{
		// デストラクターテーブル用
		rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		// ピクセルシェーダーから見える
		rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		rootParameters[1].Descriptor.ShaderRegister = 0;
		// レンジを設定
		rootParameters[1].Descriptor.RegisterSpace = 0;
	}
	// --------------
	// サンプラー
	// --------------
	D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
	{
		// 横繰り返し
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		// 縦繰り返し
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		// 奥繰り返し
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		// ボーダーのカラー
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		// 補正しない
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;

		// ミップマップ設定
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MinLOD = 0.0f;

		// ピクセルシェーダーの可視化
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		samplerDesc.ShaderRegister = 0;
		samplerDesc.RegisterSpace = 0;
		samplerDesc.MaxAnisotropy = 1;
		// オーバー時リサンプリングしない
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	}

	// --------------------------
	// ルートシグネチャーの設定
	// --------------------------
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	{
		// フラグ設定
		rootSignatureDesc.Flags =
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		// パラメーター設定
		rootSignatureDesc.pParameters = rootParameters;
		rootSignatureDesc.NumParameters = 2;

		// サンプラー設定
		rootSignatureDesc.pStaticSamplers = &samplerDesc;
		rootSignatureDesc.NumStaticSamplers = 1;
	}


	// Blob
	ComPtr<ID3DBlob> pRootSigBlob = nullptr;
	ComPtr<ID3DBlob> pErrorBlob = nullptr;

	// ルートシグネチャーのバイナリコード作成
	HRESULT result = D3D12SerializeRootSignature(
		&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0,
		&pRootSigBlob,
		&pErrorBlob
	);

	if (FAILED(result))
	{
		printf("【RootSignature】Failed when SerializeRootSignature\n");
		// エラーの情報を出力
		if (pErrorBlob)
		{
			printf("%s\n",(char*)pErrorBlob->GetBufferPointer());
		}
		return false;
	}

	// ルートシグネチャーの作成(オブジェクト化)
	result = Render_I->GetGraphics()->GetDevice()->CreateRootSignature(
		0,
		pRootSigBlob->GetBufferPointer(),
		pRootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(m_pRootSignature.GetAddressOf())
	);

	if (FAILED(result))
	{
		printf("【RootSignature】Failed when Create RootSignature Object\n");
		printf("FAILED : %08X\n", result);
		return false;
	}


	return true;
}

// 後片付け処理
void RootSignature::Term()
{
	m_pRootSignature.Reset();
}

// ルートシグネチャーを取得
ID3D12RootSignature* RootSignature::Get() const
{
	return m_pRootSignature.Get();
}