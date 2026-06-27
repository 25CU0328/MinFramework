#include "BasicShaderHeader.hlsli"

VSOutput VSMain(VSInput input)
{
    VSOutput output;

    output.svPos = mul(float4(input.position, 1.0f), mat);

    output.normal = input.normal;

    output.uv = input.uv;

    return output;
}