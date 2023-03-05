cbuffer VScbuffer : register(b0)
{
    matrix mvp;
};

struct VSInput
{
    float4 position: POSITION;
    float4 color : COLOR;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = mul(input.position, mvp);
    output.color = input.color;
    
    return output;
}
