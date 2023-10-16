cbuffer VScbuffer : register(b0)
{
    matrix mvp;
};

struct VSInput
{
    float4 position: POSITION;
    float4 color : COLOR;
    float4 normal : NORMAL;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 normal : NORMAL;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    float4 specColor = { 0.5f, 0.5f, 0.5f, 1.0f };
    output.position = mul(input.position, mvp);
    output.color = input.color;
    output.normal = input.normal;
    
    return output;
}
