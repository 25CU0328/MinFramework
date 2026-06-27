
#include "BasicShaderHeader.hlsli"

float4 PSMain(VSOutput input) : SV_TARGET
{
    float3 tempNormal = normalize(input.normal);

    // 範囲を [-1,1] から [0, 1]に調整する       
    float3 color = tempNormal * 0.5f + 0.5f;

    return float4(color, 1.0f);
}