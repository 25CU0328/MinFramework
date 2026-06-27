
struct VSInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 svPos : SV_Position;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

//0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t0); 

//0番スロットに設定されたサンプラ
SamplerState smp : register(s0); 

// 定数バッファー
cbuffer cbuff0 : register(b0)
{
    // 変換を行うための行列
    matrix mat; 
}