
#include "BasicShaderHeader.hlsli"

float4 PSMain(VSOutput input) : SV_TARGET
{
    return tex.Sample(smp, input.uv);
}