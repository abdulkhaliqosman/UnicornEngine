cbuffer VScbuffer : register(b0)
{
    matrix mvp;
    matrix model;
};

struct VSInput
{
    float4 position: POSITION;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float2 texcoord : TEXCOORD;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION0;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = mul(input.position, mvp);
    output.worldPosition = mul(input.position, model);
    output.color = input.color;
    output.normal = input.normal;
    output.texcoord = input.texcoord;
    
    return output;
}
