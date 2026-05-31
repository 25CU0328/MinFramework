
#include "BasicShaderHeader.hlsli"


float4 PSMain(VSOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);

    // マイナスは黒になるため0~1の補正を行う
    // [-1,1] -> [0,1]
    normal = normal * 0.5f + 0.5f;

    return float4(normal, 1.0f);
    // return tex.Sample(smp, input.uv);
}